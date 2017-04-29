#include "gameEngine.h"

GameEngine::GameEngine(int length)
    : bd(length), time(QTime::currentTime())
{
    for(int r = 0; r < BOARD_HEIGHT; r++)
    {
        for(int c = 0; c < BOARD_WIDTH; c++)
        {
            cell tmp = bd.get_a_cell(r, c);

            if(tmp.get_real_color() == NO_COLOR)
            {
                vaild_cells.append(bd.get_a_cell(r, c));
            }
        }
    }

    qsrand(time.msec() + time.second() * SCALAR);
    selected_cell = NULL;
    is_move = false;
    dest = NULL;
    score = 0;
}

void GameEngine::empty_trail()
{
    while(!move_trail.isEmpty())
        move_trail.removeFirst();
}

void GameEngine::set_selected_cell(int row, int column, QTimer& timer)
{
    dest = NULL;

    if(selected_cell != NULL)
        selected_cell->set_color(selected_cell->get_real_color());

    if(bd.get_a_cell(row, column).get_real_color() != NO_COLOR)
    {
        selected_cell = &(bd.get_a_cell(row, column));
        timer.start();
    }
    else
    {
        is_move = (selected_cell != NULL);
        if(is_move)
            move(*selected_cell, bd.get_a_cell(row, column));
        selected_cell = NULL;
        timer.stop();
    }
}

void GameEngine::maintain_vaild_cells(int operation, QPair<int, int>& pair)
{
    for(int i = 0; i < vaild_cells.size(); i++)
    {
        if(operation == REMOVE)
        {
            if(vaild_cells.at(i).get_position().x() == pair.first && vaild_cells.at(i).get_position().y() == pair.second)
            {
                vaild_cells.remove(i);
                break;
            }
        }
        else if(operation == APPEND)
        {
            vaild_cells.append(bd.get_a_cell(pair.first, pair.second));
            break;
        }
        else
        {
            break;
        }
    }
}

void GameEngine::move(cell& start, cell& goal)
{
    dest = &goal;
    CellTuple tuple[BOARD_HEIGHT][BOARD_WIDTH];
    bool close[BOARD_HEIGHT][BOARD_WIDTH];
    QVector<CellTuple> open;
    bool reach_dest = false;
    int num = 0;

    for(int r = 0; r < BOARD_HEIGHT; r++)
    {
        for(int c = 0; c < BOARD_WIDTH; c++)
        {
            tuple[r][c] = CellTuple(bd.get_a_cell(r, c), r, c);
            close[r][c] = false;
        }
    }

    open.append(CellTuple(start, start.get_position().x(), start.get_position().y()));

    while(!open.isEmpty() && !reach_dest)
    {
        find_least_f(open, num);
        CellTuple t = open.at(num);
        open.removeAt(num);
        close[t.get_r()][t.get_c()] = false;

        int directions[NUM_OF_DIRECTIONS];
        int x_diff = start.get_position().x() - goal.get_position().x();
        int y_diff = start.get_position().y() - goal.get_position().y();

        //Set move priority
        if(qAbs(x_diff) > qAbs(y_diff))
        {
            if(x_diff > 0)
            {
                directions[0] = UP;
                directions[3] = DOWN;
            }
            else
            {
                directions[0] = DOWN;
                directions[3] = UP;
            }

            if(y_diff > 0)
            {
                directions[1] = LEFT;
                directions[2] = RIGHT;
            }
            else
            {
                directions[1] = RIGHT;
                directions[2] = LEFT;
            }
        }
        else
        {
            if(y_diff > 0)
            {
                directions[0] = LEFT;
                directions[3] = RIGHT;
            }
            else
            {
                directions[0] = RIGHT;
                directions[3] = LEFT;
            }


            if(x_diff > 0)
            {
                directions[1] = UP;
                directions[2] = DOWN;
            }
            else
            {
                directions[1] = DOWN;
                directions[2] = UP;
            }
        }

        for(int i = 0; i < NUM_OF_DIRECTIONS; i++)
        {
            switch(directions[i])
            {
            case UP:
                check_successor(t, t.get_r() + TO_UP, t.get_c(), goal, reach_dest, open, tuple, close);
                break;

            case DOWN:
                check_successor(t, t.get_r() + TO_DOWN, t.get_c(), goal, reach_dest, open, tuple, close);
                break;

            case LEFT:
                check_successor(t, t.get_r(), t.get_c() + TO_LEFT, goal, reach_dest, open, tuple, close);
                break;

            case RIGHT:
                check_successor(t, t.get_r(), t.get_c() + TO_RIGHT, goal, reach_dest, open, tuple, close);
                break;
            }
        }
    }

    if(!reach_dest)
        empty_trail();
}

QVector<QPair<int, int>> GameEngine::build_track(CellTuple _tuple[BOARD_HEIGHT][BOARD_WIDTH], cell& goal)
{
    CellTuple _tuple_[BOARD_HEIGHT][BOARD_WIDTH];

    for(int r = 0; r < BOARD_HEIGHT; r++)
    {
        for(int c = 0; c < BOARD_WIDTH; c++)
        {
            _tuple_[r][c] = _tuple[r][c];
        }
    }

    int r = goal.get_position().x();
    int c = goal.get_position().y();

    while(!(_tuple_[r][c].get_parent().get_position().x() == r && _tuple_[r][c].get_parent().get_position().y() == c))
    {
        move_trail.append(qMakePair(r, c));
        QPoint position = _tuple_[r][c].get_parent().get_position();
        r = position.x();
        c = position.y();
    }

    move_trail.append(qMakePair(r, c));

    return move_trail;
}

bool GameEngine::check_successor(CellTuple& parent, int r, int c, cell& goal, bool& reached, QVector<CellTuple>& open, CellTuple tuple[BOARD_HEIGHT][BOARD_WIDTH], bool close[BOARD_HEIGHT][BOARD_WIDTH])
{
    if(!reached)
    {
        if(is_cell_vaild(r, c))
        {
            cell tmp = bd.get_a_cell(parent.get_r(), parent.get_c());

            if(is_destnation(r, c, goal))
            {
                tuple[r][c].set_parent(tmp);
                build_track(tuple, goal);
                reached = true;
            }
            else if(!close[r][c] && !is_blocked(r, c))
            {
                float ng = qAbs(float(parent.get_r()) - float(r)) + qAbs(float(parent.get_c()) - float(c));
                float nh = qAbs(compute_h(r, c, goal));
                float nf = ng + nh;

                if(tuple[r][c].get_f() == FLT_MAX || nf < tuple[r][c].get_f())
                {
                    tuple[r][c].set_g(ng);
                    tuple[r][c].set_h(nh);
                    tuple[r][c].set_f(nf);
                    tuple[r][c].set_parent(tmp);
                    open.append(tuple[r][c]);
                }
            }
        }
    }

    return reached;
}

float GameEngine::compute_h(int r, int c, cell& goal)
{
    float r_diff = float(r) - float(goal.get_position().x());
    float c_diff = float(c) - float(goal.get_position().y());

    return qSqrt(qPow(r_diff, SQUARE) + qPow(c_diff, SQUARE));
}

bool GameEngine::is_cell_vaild(int row, int column)
{
    return ((row >= 0) &&
            (row < BOARD_HEIGHT) &&
            (column >= 0) &&
            (column < BOARD_WIDTH));
}

bool GameEngine::is_blocked(int row, int column)
{
    return bd.get_a_cell(row, column).get_real_color() > NO_COLOR ? true : false;
}

bool GameEngine::is_destnation(int row, int column, cell& goal)
{
    return ((goal.get_position().x() == row) && (goal.get_position().y() == column));
}

CellTuple& GameEngine::find_least_f(QVector<CellTuple>& open, int& p)
{
    if(open.size() > 0)
    {
        float min = open.at(0).get_f();
        int num = 0;
        CellTuple* tmp = &open[0];

        for(int i = 0; i < open.size(); i++)
        {
            if(open.at(i).get_f() < min)
            {
                min = open.at(i).get_f();
                tmp = &open[i];
                num = i;
            }
        }

        p = num;

        return *tmp;
    }

    return *(CellTuple*)NULL;
}

void GameEngine::check_a_line(cell& base_cell)
{
    int r = base_cell.get_position().x();
    int c = base_cell.get_position().y();
    int color = base_cell.get_real_color();

    QVector<QPair<int, int>> open[ALL_DIRECTIONS];
    QVector<QPair<int, int>> should_clear;

    for(int i = 0; i < ALL_DIRECTIONS; i++)
    {
        open[i].append(qMakePair(r, c));
    }

    //Up
    repeat_search(open, r, c, TO_UP, 0, H_UP, color);

    //Down
    repeat_search(open, r, c, TO_DOWN, 0, H_DOWN, color);

    //Left
    repeat_search(open, r, c, 0, TO_LEFT, V_LEFT, color);

    //Right
    repeat_search(open, r, c, 0, TO_RIGHT, V_RIGHT, color);

    //Up Left
    repeat_search(open, r, c, TO_UP, TO_LEFT, RD_UP, color);

    //Up Right
    repeat_search(open, r, c, TO_UP, TO_RIGHT, LD_UP, color);

    //Down Left
    repeat_search(open, r, c, TO_DOWN, TO_LEFT, LD_DOWN, color);

    //Down Right
    repeat_search(open, r, c, TO_DOWN, TO_RIGHT, RD_DOWN, color);

    for(int i = 0; i < NUM_OF_DIRECTIONS; i++)
    {
        int size = open[i * DOUBLE].size() + open[i * DOUBLE + LINE_OFFSET].size() - LINE_OFFSET;

        if(size >= MIN_LINE)
        {
            score += size;
            should_clear = open[i * DOUBLE] + open[i * DOUBLE + LINE_OFFSET] + should_clear;
        }
    }

    for(int i = 0; i < should_clear.size(); i++)
    {
        QPair<int, int> pair = should_clear.at(i);

        bd.get_a_cell(pair.first, pair.second).set_color(NO_COLOR);
        bd.get_a_cell(pair.first, pair.second).set_real_color(NO_COLOR);

        maintain_vaild_cells(APPEND, pair);
    }
}

int GameEngine::repeat_search(QVector<QPair<int, int>> open[], int _r, int _c, int r_oper, int c_oper, int direction, int _color)
{
    int r = _r;
    int c = _c;
    int color = _color;

    while(color == _color)
    {
        r += r_oper;
        c += c_oper;

        if(r >= 0 && c >= 0 && r < BOARD_HEIGHT && c < BOARD_WIDTH)
        {
            if(_color == bd.get_a_cell(r, c).get_real_color())
            {
                open[direction].append(qMakePair(r, c));
            }
            else
            {
                color = bd.get_a_cell(r, c).get_color();
            }
        }
        else
        {
            break;
        }
    }

    return open[direction].size();
}

void GameEngine::place_on_board(cell* cells)
{
    int times = vaild_cells.size() >= TIMES ? TIMES : vaild_cells.size();
    int which = 0;
    int color = 0;

    for(int i = 0; i < times; i++)
    {
        which = qrand() % vaild_cells.size();
        QPoint position = vaild_cells.at(which).get_position();
        color = qrand() % TOTAL_COLOR + OFFSET;
        bd.get_a_cell(position.x(), position.y()).set_color(color);
        bd.get_a_cell(position.x(), position.y()).set_real_color(color);
        if(cells != NULL)
            *(cells + i) = bd.get_a_cell(position.x(), position.y());
        vaild_cells.remove(which);
    }
}

GameEngine::~GameEngine()
{
    selected_cell = NULL;
    dest = NULL;
}

