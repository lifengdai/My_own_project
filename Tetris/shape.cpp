#include "shape.h"

shape::shape(cell& first_cell, board& bd)
    : m_bd(bd)
{
    color = NO_COLOR;
    for(int i = 0; i < NUM_OF_CELLS; i++)
    {
        cells[i] = cell();
    }

    cells[FIRST_CELL] = first_cell;
    which_position = 0;
}

void shape::rotate()
{
    compute_rotate_positions();

    which_position++;
    which_position = which_position % NUMBER_OF_ROTATE_POSITIONS;

    if(is_vaild_position(which_position))
    {
        for(int i = 0; i < NUM_OF_CELLS; i++)
        {
            int r = rotate_positions[which_position][i].x();
            int c = rotate_positions[which_position][i].y();

            cells[i] = m_bd.get_a_cell(r, c);
        }
    }
    else
    {
        which_position--;
    }
}

bool shape::is_vaild_position(int which)
{
    bool is_vaild = false;

    for(int i = 0; i < NUM_OF_CELLS; i++)
    {
        QPoint tmp = rotate_positions[which][i];

        int x = tmp.x();
        int y = tmp.y();

        if(x >= 0 && y >= 0 && x < MAIN_BOARD_HEIGHT && y < MAIN_BOARD_WIDTH && m_bd.get_a_cell(x, y).get_color() == NO_COLOR)
            is_vaild = true;
        else
        {
            is_vaild = false;
            break;
        }
    }

    return is_vaild;
}

void shape::compute_rotate_positions()
{
    for(int i = 0; i < NUMBER_OF_ROTATE_POSITIONS; i++)
    {
        rotate_positions[i][SECOND_CELL] = cells[SECOND_CELL].get_location();
    }
}

shape::~shape()
{

}
