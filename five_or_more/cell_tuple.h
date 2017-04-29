#ifndef CELLTUPLE_H
#define CELLTUPLE_H

#include "public.h"
#include "cell.h"

class CellTuple
{
public:
    CellTuple(cell&, int, int, float _f = FLT_MAX, float _g = FLT_MAX, float _h = FLT_MAX);
    CellTuple() {}
    CellTuple(const CellTuple& _cellTuple) { copy(_cellTuple); }
    float get_f() const { return f; }
    float get_g() const { return g; }
    float get_h() const { return h; }
    int get_r() const { return r; }
    int get_c() const { return c; }
    cell& get_parent() { return parent; }
    void set_f(float _f) { f = _f; }
    void set_g(float _g) { g = _g; }
    void set_h(float _h) { h = _h; }
    void set_r(int _r) { r = _r; }
    void set_c(int _c) { c = _c; }
    void set_parent(cell& _parent) { parent = _parent; }
    CellTuple& operator=(const CellTuple& _cellTuple) { return copy(_cellTuple); }
    ~CellTuple();
private:
    float f;
    float g;
    float h;
    int r;
    int c;
    cell parent;
    CellTuple& copy(const CellTuple&);
};

#endif // CELLTUPLE_H
