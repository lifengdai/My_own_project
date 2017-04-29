#ifndef BOARD_H
#define BOARD_H

#include "public.h"
#include "cell.h"

class Board
{
public:
    Board(int length);
    cell& get_a_cell(int, int) const;
    ~Board();
private:
    cell(* cells)[BOARD_HEIGHT];
};

#endif // BOARD_H
