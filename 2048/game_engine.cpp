#include "game_engine.h"

gameEngine::gameEngine(int x, int y)
    : gd(x, y)
{
    QTime time = QTime::currentTime();
    int seed = time.msec() + time.second() * TIME_SCALR;
    qsrand(seed);
    move_is_started = false;
}

void gameEngine::place_on_grid()
{
    if(gd.get_empty_cells().size() > 0)
    {
        int size = gd.get_empty_cells().size();
        int rand_place = qrand() % size;

        const QPair<int, int>& pair = gd.pop_location(rand_place);

        int r = pair.first;
        int c = pair.second;

        gd.get_a_cell(r,c).set_number_and_color(TWO);
    }
}

void gameEngine::move_left()
{
    move(TO_LEFT, LEFT_UP_SPEED, ACTUAL_MOVE);
}

void gameEngine::move_right()
{
    move(TO_RIGHT, RIGHT_DOWN_SPEED, ACTUAL_MOVE);
}

void gameEngine::move_up()
{
    move(TO_UP, LEFT_UP_SPEED, ACTUAL_MOVE);
}

void gameEngine::move_down()
{
    move(TO_DOWN, RIGHT_DOWN_SPEED, ACTUAL_MOVE);
}

void gameEngine::test_move(int direction)
{
    move(direction, RIGHT_DOWN_SPEED, TEST_MOVE);
}

void gameEngine::move(int direction, int speed, int num)
{
    int num_move_done = 0;

    for(int i = 0; i < need_to_move.size(); i++)
    {
        cell& tmp = need_to_move[i];
        QPointF& position = tmp.get_position();
        QPair<int, int>& tmp_pair = move_to_where[i];
        const cell& target_cell = gd.get_a_cell(tmp_pair.first, tmp_pair.second);

        if(is_moveable(direction, position, target_cell, tmp_pair))
        {
            if(num == ACTUAL_MOVE)
            {
                int current_position = 0;

                switch(direction)
                {
                case TO_RIGHT:
                case TO_LEFT:
                    current_position = tmp.get_position().x();
                    current_position += speed;
                    tmp.get_position().setX(current_position);
                    break;

                case TO_UP:
                case TO_DOWN:
                    current_position = tmp.get_position().y();
                    current_position += speed;
                    tmp.get_position().setY(current_position);
                    break;
                }
            }
        }
        else
        {
            num_move_done++;
        }
    }

    if(num_move_done == need_to_move.size())
    {
        move_is_started = false;
    }
}

bool gameEngine::is_moveable(int direction, const QPointF& position, const cell& target_cell, const QPair<int, int>& tmp_pair)
{
    bool moveable = false;

    switch(direction)
    {
    case TO_LEFT:
        moveable = position.x() > target_cell.get_position().x() && tmp_pair.first != NOT_MOVEABLE;
        break;

    case TO_RIGHT:
        moveable = position.x() < target_cell.get_position().x() && tmp_pair.first != NOT_MOVEABLE;
        break;

    case TO_UP:
        moveable = position.y() > target_cell.get_position().y() && tmp_pair.first != NOT_MOVEABLE;
        break;

    case TO_DOWN:
        moveable = position.y() < target_cell.get_position().y() && tmp_pair.first != NOT_MOVEABLE;
        break;
    }

    return moveable;
}

bool gameEngine::is_out_of_range(int direction, int r, int c)
{
    bool out_of_range = false;

    switch(direction)
    {
    case TO_LEFT:
        out_of_range = c + LEFT < 0;
        break;

    case TO_RIGHT:
        out_of_range = c + RIGHT >= GRID_WIDTH;
        break;

    case TO_UP:
        out_of_range = r + UP < 0;
        break;

    case TO_DOWN:
        out_of_range = r + DOWN >= GRID_HEIGHT;
        break;
    }

    return out_of_range;
}

void gameEngine::asign_move_type_left()
{
    asign_move_type(TO_LEFT);
}

void gameEngine::asign_move_type_right()
{
    asign_move_type(TO_RIGHT);
}

void gameEngine::asign_move_type_up()
{
    asign_move_type(TO_UP);
}

void gameEngine::asign_move_type_down()
{
    asign_move_type(TO_DOWN);
}

bool gameEngine::i_is_out_of_range(int direction, int i, int size)
{
    bool is_out = false;

    switch(direction)
    {
    case TO_UP:
    case TO_LEFT:
        is_out = i < size;
        break;

    case TO_DOWN:
    case TO_RIGHT:
        is_out = i >= 0;
        break;
    }

    return is_out;
}

void gameEngine::asign_move_type(int direction)
{
    move_to_where.clear();

    for(int i = 0; i < need_to_move.size(); i++)
    {
        const cell& tmp = need_to_move.at(i);
        int r = tmp.get_location().x();
        int c = tmp.get_location().y();
        int num = tmp.get_number();
        int move_type = MOVE_TYPE_INIT;
        int p = 0;

        gd.get_a_cell(r, c).set_number_and_color(EMPTY);

        if(is_out_of_range(direction, r, c))
        {
            gd.get_a_cell(r, c).set_number_and_color(num);
            move_to_where.append(qMakePair(NOT_MOVEABLE, NOT_MOVEABLE));
        }
        else
        {
            check(direction, r, c, move_type, p, tmp);

            if(direction == TO_LEFT || direction == TO_RIGHT)
                fill_where_to_move(move_type, r, c, r, p, num);
            else
                fill_where_to_move(move_type, r, c, p, c, num);
        }
    }
}

void gameEngine::check(int direction, int r, int c, int& move_type, int& p, const cell& tmp)
{
    int i = 0;
    int k = 0;

    switch(direction)
    {
    case TO_LEFT:
        i = c + LEFT;
        k = LEFT;
        break;

    case TO_RIGHT:
        i = c + RIGHT;
        k = RIGHT;
        break;

    case TO_UP:
        i = r + UP;
        k = UP;
        break;

    case TO_DOWN:
        i = r + DOWN;
        k = DOWN;
        break;
    }

    for(int j = i; j_is_out_of_range(direction, j); j += k)
    {
        int m = 0;
        if(is_empty(direction, r, c, j))
        {
            move_type = MOVE_TYPE_EMPTY;
            move_is_started = true;
            p = j;
            ++m;
            continue;
        }

        if(is_the_same(direction, r, c, j, tmp))
        {
            move_type = MOVE_TYPE_ADD;
            move_is_started = true;
            p = j;
            break;
        }

        if(is_notmoveable(direction, r, c, j, tmp, p))
        {
            move_type = MOVE_TYPE_NOT_MOVEABLE;
            break;
        }
    }

}

bool gameEngine::j_is_out_of_range(int direction, int j)
{
    bool jIsOutOfRange = false;

    switch(direction)
    {
    case TO_LEFT:
        jIsOutOfRange = j >= 0;
        break;

    case TO_RIGHT:
        jIsOutOfRange = j < GRID_WIDTH;
        break;

    case TO_UP:
        jIsOutOfRange = j >= 0;
        break;

    case TO_DOWN:
        jIsOutOfRange = j < GRID_HEIGHT;
        break;
    }

    return jIsOutOfRange;
}

bool gameEngine::is_empty(int direction, int r, int c, int j)
{
    bool isEmpty = false;

    switch(direction)
    {
    case TO_LEFT:
    case TO_RIGHT:
        isEmpty = gd.get_a_cell(r, j).get_number() == EMPTY;
        break;

    case TO_UP:
    case TO_DOWN:
        isEmpty = gd.get_a_cell(j, c).get_number() == EMPTY;
        break;
    }

    return isEmpty;
}

bool gameEngine::is_the_same(int direction, int r, int c, int j, const cell& tmp)
{
    bool isSame = false;

    switch(direction)
    {
    case TO_LEFT:
    case TO_RIGHT:
        isSame = gd.get_a_cell(r, j).get_number() == tmp.get_number();
        break;

    case TO_UP:
    case TO_DOWN:
        isSame = gd.get_a_cell(j, c).get_number() == tmp.get_number();
        break;
    }

    return isSame;
}

bool gameEngine::is_notmoveable(int direction, int r, int c, int j, const cell& tmp, int& p)
{
    bool isNotmoveable = false;

    switch(direction)
    {
    case TO_LEFT:
        isNotmoveable = gd.get_a_cell(r, j).get_number() != EMPTY && gd.get_a_cell(r, j).get_number() != tmp.get_number();
        p = j + 1;
        break;

    case TO_RIGHT:
        isNotmoveable = gd.get_a_cell(r, j).get_number() != EMPTY && gd.get_a_cell(r, j).get_number() != tmp.get_number();
        p = j - 1;
        break;

    case TO_UP:
        isNotmoveable = gd.get_a_cell(j, c).get_number() != EMPTY && gd.get_a_cell(j, c).get_number() != tmp.get_number();
        p = j + 1;
        break;

    case TO_DOWN:
        isNotmoveable = gd.get_a_cell(j, c).get_number() != EMPTY && gd.get_a_cell(j, c).get_number() != tmp.get_number();
        p = j - 1;
        break;
    }

    return isNotmoveable;
}

void gameEngine::fill_where_to_move(int move_type, int r, int c, int r_p, int c_p, int num)
{
    switch (move_type)
    {
    case MOVE_TYPE_NOT_MOVEABLE:
    case MOVE_TYPE_EMPTY:
    {
        move_to_where.append(qMakePair(r_p, c_p));
        gd.get_a_cell(r_p, c_p).set_number_and_color(num);
        QPair<int, int> tmp_pair = qMakePair(r, c);
        gd.add_location(tmp_pair);
        gd.get_empty_cells().removeOne(qMakePair(r_p, c_p));
    }
        break;

    case MOVE_TYPE_ADD:
    {
        move_to_where.append(qMakePair(r_p, c_p));
        num = gd.get_a_cell(r_p, c_p).get_number();
        gd.get_a_cell(r_p, c_p).set_number_and_color(num + num);
        QPair<int, int> tmp_pair = qMakePair(r, c);
        gd.add_location(tmp_pair);
    }
        break;

    default:
        break;
    }
}

void gameEngine::up_fill()
{
    need_to_move.clear();

    for(int r = 0; r < GRID_HEIGHT; r++)
    {
        for(int c = 0; c < GRID_WIDTH; c++)
        {
            fill_need_to_move(r, c);
        }
    }
}

void gameEngine::left_fill()
{
    need_to_move.clear();

    for(int c = 0; c < GRID_WIDTH; c++)
    {
        for(int r = 0; r < GRID_HEIGHT; r++)
        {
            fill_need_to_move(r, c);
        }
    }
}

void gameEngine::right_fill()
{
    need_to_move.clear();

    for(int c = GRID_WIDTH - 1; c >= 0; c--)
    {
        for(int r = GRID_HEIGHT - 1; r >= 0; r--)
        {
            fill_need_to_move(r, c);
        }
    }
}

void gameEngine::down_fill()
{
    need_to_move.clear();

    for(int r = GRID_HEIGHT - 1; r >= 0; r--)
    {
        for(int c = GRID_WIDTH - 1; c >= 0; c--)
        {
            fill_need_to_move(r, c);
        }
    }
}

void gameEngine::fill_need_to_move(int r, int c)
{
    if(gd.get_a_cell(r, c).get_number() != EMPTY)
    {
        cell tmp = gd.get_a_cell(r, c);
        need_to_move.append(tmp);
    }
}

gameEngine::~gameEngine()
{

}
