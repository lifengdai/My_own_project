#ifndef BOARD_H
#define BOARD_H

#include "public.h"
#include "cell.h"

class board
{
public:
    board() {  }
    board(int, int, int, int);
    board(const board& bd) { copy(bd); }
    cell& get_a_cell(int, int) const;
    void clear_board();
    void set_cell_color(cell &, int);
    void update_rows();
    int get_cell_color(cell &);
    bool is_full(int);
    bool is_empty(int);
    bool is_something(int);
    void clear_row(int);
    void row_cut_paste(int, int);
    const QPoint get_start_location(int, int, int);
    board& operator=(const board& bd) { return copy(bd); }
    ~board();

private:
    board& copy(const board&);
    cell* cells;
    int board_h;
    int board_w;
};

#endif // BOARD_H
