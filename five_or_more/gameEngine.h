#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "public.h"
#include "board.h"
#include "cell.h"
#include "cell_tuple.h"

class GameEngine
{
public:
    GameEngine(int length);
    QVector<QPair<int, int>>& get_trail() { return move_trail; }
    void empty_trail();
    Board& get_bd() { return bd; }
    cell*& get_dest() { return dest; }
    int get_score() { return score; }
    void place_on_board(cell* cells = NULL);
    void set_selected_cell(int, int, QTimer &);
    void move(cell&, cell&);
    void maintain_vaild_cells(int, QPair<int, int>&);
    bool is_cell_vaild(int, int);
    bool is_blocked(int, int);
    bool is_destnation(int, int, cell&);
    bool Is_move() { return is_move; }
    void check_a_line(cell&);
    int repeat_search(QVector<QPair<int, int>> open[], int, int, int, int, int, int);
    bool check_successor(CellTuple&, int, int, cell&, bool&, QVector<CellTuple>&, CellTuple tuple[BOARD_HEIGHT][BOARD_WIDTH], bool[BOARD_HEIGHT][BOARD_WIDTH]);    
    float compute_h(int, int, cell&);
    QVector<QPair<int, int>> build_track(CellTuple _tuple[BOARD_HEIGHT][BOARD_WIDTH], cell&);
    CellTuple& find_least_f(QVector<CellTuple> &, int &);
    cell*& get_selected_cell() { return selected_cell; }
    ~GameEngine();
private:
    bool is_move;
    int score;
    Board bd;
    QTime time;
    cell* selected_cell;
    cell* dest;
    QVector<cell> vaild_cells;
    QVector<QPair<int, int>> move_trail;
};

#endif // GAMEENGINE_H
