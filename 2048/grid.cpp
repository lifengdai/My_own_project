#include "grid.h"

grid::grid(int x, int y)
{
    cells = new cell[GRID_HEIGHT][GRID_WIDTH];

    for(int r = 0; r < GRID_HEIGHT; r++)
    {
        for(int c = 0; c < GRID_WIDTH; c++)
        {
            int _x = c * CELL_LENGTH + x;
            int _y = r * CELL_LENGTH + y;

            cells[r][c] = cell(r, c, _x, _y, EMPTY);
            empty_cells.append(qMakePair<int, int>(r, c));
        }
    }
}

QPair<int, int> grid::pop_location(int index)
{
    QPair<int, int> tmp = empty_cells.at(index);
    empty_cells.remove(index);
    return tmp;
}

void grid::add_location(QPair<int, int>& _location)
{
    empty_cells.append(_location);
}

grid::~grid()
{
    delete[] cells;
    cells = NULL;
}
