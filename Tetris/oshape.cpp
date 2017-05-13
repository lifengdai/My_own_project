#include "oshape.h"

oshape::oshape(cell& first_cell, board& bd)
    : shape(first_cell, bd)
{
    color = ORANGE;
    int r = first_cell.get_location().x();
    int c = first_cell.get_location().y();

    cells[SECOND_CELL] = bd.get_a_cell(r, c + RIGHT);
    cells[THIRD_CELL] = bd.get_a_cell(r + UP, c);
    cells[FOUTH_CELL] = bd.get_a_cell(r + UP, c + RIGHT);

    for(int i = 0; i < NUM_OF_CELLS; i++)
    {
        bd.set_cell_color(cells[i], color);
    }
}

void oshape::rotate()
{

}

void oshape::compute_rotate_positions()
{

}

oshape::~oshape()
{

}
