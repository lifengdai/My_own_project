#include "board.h"

Board::Board(int length)
{
    cells = new cell[BOARD_WIDTH][BOARD_HEIGHT];
    cell::length = float(length) / float(BOARD_HEIGHT);

    for(int r = 0; r < BOARD_WIDTH; r++)
    {
        for(int c = 0; c < BOARD_HEIGHT; c++)
        {
            float x = OFFSET_X + float(c) * cell::length;
            float y = OFFSET_Y + float(r) * cell::length;

            QPointF point(x, y);
            QPoint position(r, c);
            cells[r][c] = cell(point, position, NO_COLOR);
        }
    }
}

cell& Board::get_a_cell(int row, int column) const
{
    if(row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH)
        return cells[row][column];
    else
        return *(cell*)NULL;
}

Board::~Board()
{
    delete[] cells;
    cells = NULL;
}

