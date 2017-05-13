#include "ishape.h"

ishape::ishape(cell& first_cell, board& bd)
    : shape(first_cell, bd)
{
    color = GRAY;
    int r = first_cell.get_location().x();
    int c = first_cell.get_location().y();

    cells[SECOND_CELL] = bd.get_a_cell(r + UP, c);
    cells[THIRD_CELL] = bd.get_a_cell(r + UP + UP, c);
    cells[FOUTH_CELL] = bd.get_a_cell(r + UP + UP + UP, c);

    for(int i = 0; i < NUM_OF_CELLS; i++)
    {
        bd.set_cell_color(cells[i], color);
    }
}

void ishape::compute_rotate_positions()
{
    shape::compute_rotate_positions();

    int r = rotate_positions[FIRST_POSITION][SECOND_CELL].x();
    int c = rotate_positions[FIRST_POSITION][SECOND_CELL].y();

    rotate_positions[FIRST_POSITION][FIRST_CELL] = QPoint(r + DOWN, c);
    rotate_positions[FIRST_POSITION][THIRD_CELL] = QPoint(r + UP, c);
    rotate_positions[FIRST_POSITION][FOUTH_CELL] = QPoint(r + UP + UP, c);

    rotate_positions[SECOND_POSITION][FIRST_CELL] = QPoint(r, c + LEFT);
    rotate_positions[SECOND_POSITION][THIRD_CELL] = QPoint(r, c + RIGHT);
    rotate_positions[SECOND_POSITION][FOUTH_CELL] = QPoint(r, c + RIGHT + RIGHT);

    rotate_positions[THIRD_POSITION][FIRST_CELL] = QPoint(r + UP, c);
    rotate_positions[THIRD_POSITION][THIRD_CELL] = QPoint(r + DOWN, c);
    rotate_positions[THIRD_POSITION][FOUTH_CELL] = QPoint(r + DOWN + DOWN, c);

    rotate_positions[FOUTH_POSITION][FIRST_CELL] = QPoint(r, c + RIGHT);
    rotate_positions[FOUTH_POSITION][THIRD_CELL] = QPoint(r, c + LEFT);
    rotate_positions[FOUTH_POSITION][FOUTH_CELL] = QPoint(r, c + LEFT + LEFT);
}

ishape::~ishape()
{

}
