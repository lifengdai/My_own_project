#ifndef SHAPE_H
#define SHAPE_H

#include "public.h"
#include "cell.h"
#include "board.h"

class shape
{
public:
    shape(cell &, board& bd);
    virtual ~shape() = 0;
    virtual void rotate();
    int get_color() { return color; }
    cell& get_a_cell(int n) { return cells[n]; }
    void set_a_cell(int n, cell& _cell) { cells[n] = _cell; }

protected:
    virtual void compute_rotate_positions();
    bool is_vaild_position(int);
    int color;
    cell cells[NUM_OF_CELLS];
    QPoint rotate_positions[NUMBER_OF_ROTATE_POSITIONS][NUM_OF_CELLS];
    int which_position;
    board m_bd;
};

#endif // SHAPE_H
