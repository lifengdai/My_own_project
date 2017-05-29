#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include "grid.h"
#include "cell.h"

class gameEngine
{
public:
    gameEngine(int, int);
    void place_on_grid();
    grid& get_grid() { return gd; }
    cell& get_need_to_move_cell(int i) { return need_to_move[i]; }
    QVector<cell>& get_need_to_move() { return need_to_move; }
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    void test_move(int direction);
    void up_fill();
    void left_fill();
    void right_fill();
    void down_fill();
    void asign_move_type_left();
    void asign_move_type_right();
    void asign_move_type_up();
    void asign_move_type_down();
    bool get_move_is_started() { return move_is_started; }
    void set_move_is_started(bool flag) { move_is_started = flag; }
    ~gameEngine();

private:
    grid gd;
    QVector<cell> need_to_move;
    void check(int, int, int, int &, int&, const cell&);
    void asign_move_type(int);
    void move(int, int, int);
    bool is_moveable(int, const QPointF&, const cell&, const QPair<int, int>&);
    QVector<QPair<int, int>> move_to_where;
    bool j_is_out_of_range(int, int);
    bool i_is_out_of_range(int, int, int);
    bool is_out_of_range(int, int, int);
    bool is_empty(int, int, int, int);
    bool is_the_same(int, int, int, int, const cell&);
    bool is_notmoveable(int, int, int, int, const cell&, int&);
    void fill_where_to_move(int, int, int, int, int, int);
    void fill_need_to_move(int, int);
    bool move_is_started;
};

#endif // GAME_ENGINE_H
