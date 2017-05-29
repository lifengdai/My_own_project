#ifndef GRID_H
#define GRID_H

#include "public.h"
#include "cell.h"

class grid
{
public:
    grid(int, int);
    QPair<int, int> pop_location(int);
    void add_location(QPair<int, int>&);
    QVector<QPair<int, int>>& get_empty_cells() { return empty_cells; }
    cell& get_a_cell(int r, int c) { return cells[r][c]; }
    ~grid();

private:
    cell(* cells)[GRID_WIDTH];
    QVector<QPair<int, int>> empty_cells;
};

#endif // GRID_H
