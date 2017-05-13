#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "public.h"
#include "board.h"
#include "cell.h"
#include "shape.h"
#include "oshape.h"
#include "sshape.h"
#include "zshape.h"
#include "tshape.h"
#include "ishape.h"
#include "jshape.h"
#include "lshape.h"

class gameEngine
{
public:
    gameEngine(int, int, int, int);
    board& get_main_bd() { return main_bd; }
    board& get_next_bd() { return next_bd; }
    bool get_move_down_ok() { return move_down_ok; }
    void next_place_a_shape();
    void main_place_a_shape();
    void move_down();
    void move_left();
    void move_right();
    void clear_rows();
    int num_rows_cld();
    void rows_move_down();
    void rotate();
    int compute_score();
    ~gameEngine();

private:
    void traverse_rows(int* cld_rows = NULL);
    int set_shape_color(int);
    shape* place_a_shape(board &, int, int, int);
    bool is_moveable(int, int, bool);
    void move(int, int);
    board main_bd;
    board next_bd;
    int m_ishape;
    shape* tracked_shape;
    bool move_down_ok;
};

#endif // GAME_ENGINE_H
