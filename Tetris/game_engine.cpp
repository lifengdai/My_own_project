#include "game_engine.h"

gameEngine::gameEngine(int main_x, int main_y, int next_x, int next_y)
    : main_bd(main_x, main_y, MAIN_BOARD_HEIGHT, MAIN_BOARD_WIDTH),
      next_bd(next_x, next_y, NEXT_BOARD_HEIGHT, NEXT_BOARD_WIDTH)
{
    QTime time = QTime::currentTime();
    int seed = time.second() * TIME_SCALAR + time.msec();
    m_ishape = 0;
    move_down_ok = true;
    tracked_shape = NULL;
    qsrand(seed);
}

int gameEngine::set_shape_color(int _color)
{
    int color = tracked_shape->get_color();

    for(int i = 0; i < NUM_OF_CELLS; i++)
    {
        QPoint tmp = tracked_shape->get_a_cell(i).get_location();

        int r = tmp.x();
        int c = tmp.y();

        main_bd.get_a_cell(r, c).set_color(_color);
    }

    return color;
}

void gameEngine::rotate()
{
    set_shape_color(NO_COLOR);

    tracked_shape->rotate();

    set_shape_color(tracked_shape->get_color());
}

shape* gameEngine::place_a_shape(board& bd, int hrz, int vrtx, int num)
{
    shape* _shape = NULL;

    switch (num)
    {
    case L_SHAPE:
    {
        const QPoint point = bd.get_start_location(L_SHAPE, hrz, vrtx);
        cell& tmp = bd.get_a_cell(point.x(), point.y());
        _shape = new lshape(tmp, bd);
    }
        break;
    case J_SHAPE:
    {
        const QPoint point = bd.get_start_location(J_SHAPE, hrz, vrtx);
        cell& tmp = bd.get_a_cell(point.x(), point.y());
        _shape = new jshape(tmp, bd);
    }
        break;

    case I_SHAPE:
    {
        const QPoint point = bd.get_start_location(I_SHAPE, hrz, vrtx);
        cell& tmp = bd.get_a_cell(point.x(), point.y());
        _shape = new ishape(tmp, bd);
    }
        break;

    case T_SHAPE:
    {
        const QPoint point = bd.get_start_location(T_SHAPE, hrz, vrtx);
        cell& tmp = bd.get_a_cell(point.x(), point.y());
        _shape = new tshape(tmp, bd);
    }
        break;

    case Z_SHAPE:
    {
        const QPoint point = bd.get_start_location(Z_SHAPE, hrz, vrtx);
        cell& tmp = bd.get_a_cell(point.x(), point.y());
        _shape = new zshape(tmp, bd);
    }
        break;

    case S_SHAPE:
    {
        const QPoint point = bd.get_start_location(S_SHAPE, hrz, vrtx);
        cell& tmp = bd.get_a_cell(point.x(), point.y());
        _shape = new sshape(tmp, bd);
    }
        break;

    case O_SHAPE:
    {
        const QPoint point = bd.get_start_location(O_SHAPE, hrz, vrtx);
        cell& tmp = bd.get_a_cell(point.x(), point.y());
        _shape = new oshape(tmp, bd);
    }
        break;

    default:
        break;
    }

    return _shape;
}

void gameEngine::next_place_a_shape()
{
    int ishape = qrand() % NUM_OF_SHAPES;
    place_a_shape(next_bd, HRZ_CENTER, VRTX_CENTER, ishape);
    m_ishape = ishape;
}

void gameEngine::main_place_a_shape()
{
    move_down_ok = true;

    if(tracked_shape != NULL)
    {
        delete tracked_shape;
        tracked_shape = NULL;
    }

    tracked_shape = place_a_shape(main_bd, HRZ_CENTER, VRTX_START, m_ishape);
}

void gameEngine::clear_rows()
{
    traverse_rows();
}

int gameEngine::num_rows_cld()
{
    int num = 0;

    traverse_rows(&num);

    return num;
}

void gameEngine::traverse_rows(int* cld_rows)
{
    for(int i = MAIN_BOARD_HEIGHT - BIAS; i >= 0; i--)
    {
        if(main_bd.is_full(i))
        {
            if(cld_rows == NULL)
            {
                main_bd.clear_row(i);
            }
            else
            {
                ++*cld_rows;
            }
        }
    }
}

int gameEngine::compute_score()
{
    int num = num_rows_cld();

    return num * num;
}

void gameEngine::rows_move_down()
{
    int pointer_empty = MAIN_BOARD_HEIGHT - BIAS;
    int pointer_something = pointer_empty;

    for(int i = pointer_empty; i >= 0; i--)
    {
        if(main_bd.is_empty(i))
        {
            pointer_something = i - BIAS;

            for(int j = pointer_something; j >=0; j--)
            {
                if(main_bd.is_something(j))
                {
                    main_bd.row_cut_paste(j, i);
                    break;
                }
            }
        }
    }
}

void gameEngine::move_down()
{
    bool moveable = is_moveable(DOWN, NO_MOVE, true);
    if(moveable) move(DOWN, NO_MOVE);
}

void gameEngine::move_left()
{
    bool moveable = is_moveable(NO_MOVE, LEFT, false);
    if(moveable) move(NO_MOVE, LEFT);
}

void gameEngine::move_right()
{
    bool moveable = is_moveable(NO_MOVE, RIGHT, false);
    if(moveable) move(NO_MOVE, RIGHT);
}

bool gameEngine::is_moveable(int up_down, int left_right, bool is_move_down)
{
    bool move_able = false;
    int color = NO_COLOR;

    for(int i = 0; i < NUM_OF_CELLS; i++)
    {
        cell& tmp = tracked_shape->get_a_cell(i);
        color = main_bd.get_cell_color(tmp);
        main_bd.set_cell_color(tmp, NO_COLOR);
    }

    for(int i = 0; i < NUM_OF_CELLS; i++)
    {
        int r = tracked_shape->get_a_cell(i).get_location().x();
        int c = tracked_shape->get_a_cell(i).get_location().y();

        r += up_down;
        c += left_right;

        if(r >= 0 && r < MAIN_BOARD_HEIGHT && c >= 0 && c < MAIN_BOARD_WIDTH && main_bd.get_a_cell(r, c).get_color() == NO_COLOR)
        {
            move_able = true;
        }
        else
        {
            if((r >= MAIN_BOARD_HEIGHT || main_bd.get_a_cell(r, c).get_color() != NO_COLOR) && is_move_down)
            {
                move_down_ok = false;
            }

            move_able = false;
            break;
        }
    }

    if(!move_able)
    {
        for(int i = 0; i < NUM_OF_CELLS; i++)
        {
            cell& tmp = tracked_shape->get_a_cell(i);
            main_bd.set_cell_color(tmp, color);
        }
    }

    return move_able;
}

void gameEngine::move(int up_down, int left_right)
{
    for(int i = 0; i < NUM_OF_CELLS; i++)
    {
        cell& tmp = tracked_shape->get_a_cell(i);

        int r = tmp.get_location().x();
        int c = tmp.get_location().y();

        r += up_down;
        c += left_right;

        cell& pass = main_bd.get_a_cell(r, c);

        tracked_shape->set_a_cell(i, pass);

        main_bd.set_cell_color(pass, tracked_shape->get_color());
    }
}

gameEngine::~gameEngine()
{

}
