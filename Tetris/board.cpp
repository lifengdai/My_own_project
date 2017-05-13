#include "board.h"

board::board(int x, int y, int board_height, int board_width)
{
    board_h = board_height;
    board_w = board_width;

    cells = new cell[board_height * board_width];

    for(int r = 0; r < board_height; r++)
    {
        for(int c = 0; c < board_width; c++)
        {
            float _x = float(c) * float(CELL_LENGTH) + float(x);
            float _y = float(r) * float(CELL_LENGTH) + float(y);

            QPoint location(r, c);
            QPointF position(_x, _y);

            cells[r * board_width + c] = cell(location, position);
        }
    }
}

void board::set_cell_color(cell& _cell, int _color)
{
    int _index = _cell.get_location().x() * board_w + _cell.get_location().y();
    cells[_index].set_color(_color);
}

int board::get_cell_color(cell& _cell)
{
    int _index = _cell.get_location().x() * board_w + _cell.get_location().y();
    return cells[_index].get_color();
}

void board::clear_board()
{
    for(int r = 0; r < board_h; r++)
    {
        for(int c = 0; c < board_w; c++)
        {
            cells[r * board_w + c].set_color(NO_COLOR);
        }
    }
}

const QPoint board::get_start_location(int _shape, int hrz, int vrtx)
{
    int h = 0;
    int w = 0;

    switch (_shape)
    {
    case L_SHAPE:
        w = (hrz == HRZ_CENTER ? board_w / HALF : ALL_HRZ_START_LOCATION);
        h = (vrtx == VRTX_CENTER ? board_w / HALF + BIAS : J_L_VRTX_START_LOCATION);
        break;

    case J_SHAPE:
        w = (hrz == HRZ_CENTER ? board_w / HALF - BIAS : ALL_HRZ_START_LOCATION);
        h = (vrtx == VRTX_CENTER ? board_w / HALF + BIAS : J_L_VRTX_START_LOCATION);
        break;

    case I_SHAPE:
        w = (hrz == HRZ_CENTER ? board_w / HALF : ALL_HRZ_START_LOCATION);
        h = (vrtx == VRTX_CENTER ? board_w / HALF + BIAS : I_VRTX_START_LOCATION);
        break;

    case Z_SHAPE:
        w = (hrz == HRZ_CENTER ? board_w / HALF + BIAS : ALL_HRZ_START_LOCATION);
        h = (vrtx == VRTX_CENTER ? board_w / HALF : S_O_Z_T_VRTX_START_LOCATION);
        break;

    case T_SHAPE:
        w = (hrz == HRZ_CENTER ? board_w / HALF : ALL_HRZ_START_LOCATION);
        h = (vrtx == VRTX_CENTER ? board_w / HALF : S_O_Z_T_VRTX_START_LOCATION);
        break;

    case S_SHAPE:
    case O_SHAPE:
        w = (hrz == HRZ_CENTER ? board_w / HALF - BIAS : ALL_HRZ_START_LOCATION);
        h = (vrtx == VRTX_CENTER ? board_w / HALF : S_O_Z_T_VRTX_START_LOCATION);
        break;

    default:
        break;
    }

    return QPoint(h, w);
}

cell& board::get_a_cell(int r, int c) const
{
    return cells[r * board_w + c];
}

bool board::is_full(int num)
{
    int count = 0;

    for(int c = 0; c < board_w; c++)
    {
        count = (cells[num * board_w + c].get_color() != NO_COLOR ? ++count : count);
    }

    return (count == board_w);
}

bool board::is_empty(int num)
{
    int count = 0;

    for(int c = 0; c < board_w; c++)
    {
        count = (cells[num * board_w + c].get_color() == NO_COLOR ? ++count : count);
    }

    return (count == board_w);
}

bool board::is_something(int num)
{
    return (!is_empty(num) && !is_full(num));
}

void board::clear_row(int num)
{
    for(int c = 0; c < board_w; c++)
    {
        cells[num * board_w + c].set_color(NO_COLOR);
    }
}

void board::row_cut_paste(int from, int to)
{
    for(int c = 0; c < board_w; c++)
    {
        int color = cells[from * board_w + c].get_color();
        cells[to * board_w + c].set_color(color);
        cells[from * board_w + c].set_color(NO_COLOR);
    }
}

board& board::copy(const board& bd)
{
    board_h = bd.board_h;
    board_w = bd.board_w;

    cells = new cell[board_h * board_w];

    for(int r = 0; r < board_h; r++)
    {
        for(int c = 0; c < board_w; c++)
        {
            cells[r * board_w + c] = bd.cells[r * board_w + c];
        }
    }

    return *this;
}

board::~board()
{
    delete[] cells;
    cells = NULL;
}
