#include "tshape.h"

tshape::tshape(cell& first_cell, board& bd)
    : shape(first_cell, bd)
{
    color = RED;
    int r = first_cell.get_location().x();
    int c = first_cell.get_location().y();

    cells[SECOND_CELL] = bd.get_a_cell(r + UP, c);
    cells[THIRD_CELL] = bd.get_a_cell(r + UP, c + LEFT);
    cells[FOUTH_CELL] = bd.get_a_cell(r + UP, c + RIGHT);

    for(int i = 0; i < NUM_OF_CELLS; i++)
    {
        bd.set_cell_color(cells[i], color);
    }
}

void tshape::compute_rotate_positions()
{
    shape::compute_rotate_positions();

    int r = rotate_positions[FIRST_POSITION][SECOND_CELL].x();
    int c = rotate_positions[FIRST_POSITION][SECOND_CELL].y();

    rotate_positions[FIRST_POSITION][FIRST_CELL] = QPoint(r + DOWN, c);
    rotate_positions[FIRST_POSITION][THIRD_CELL] = QPoint(r + DOWN, c + LEFT);
    rotate_positions[FIRST_POSITION][FOUTH_CELL] = QPoint(r + DOWN, c + RIGHT);

    rotate_positions[SECOND_POSITION][FIRST_CELL] = QPoint(r, c + LEFT);
    rotate_positions[SECOND_POSITION][THIRD_CELL] = QPoint(r + UP, c + LEFT);
    rotate_positions[SECOND_POSITION][FOUTH_CELL] = QPoint(r + DOWN, c + LEFT);

    rotate_positions[THIRD_POSITION][FIRST_CELL] = QPoint(r + UP, c);
    rotate_positions[THIRD_POSITION][THIRD_CELL] = QPoint(r + UP, c + LEFT);
    rotate_positions[THIRD_POSITION][FOUTH_CELL] = QPoint(r + UP, c + RIGHT);

    rotate_positions[FOUTH_POSITION][FIRST_CELL] = QPoint(r, c + RIGHT);
    rotate_positions[FOUTH_POSITION][THIRD_CELL] = QPoint(r + UP, c + RIGHT);
    rotate_positions[FOUTH_POSITION][FOUTH_CELL] = QPoint(r + DOWN, c + RIGHT);
}

tshape::~tshape()
{

}
