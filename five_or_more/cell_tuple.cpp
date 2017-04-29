#include "cell_tuple.h"

CellTuple::CellTuple(cell& _parent, int _r, int _c, float _f, float _g, float _h)
    : parent(_parent)
{
    r = _r;
    c = _c;
    f = _f;
    g = _g;
    h = _h;
}

CellTuple::~CellTuple()
{

}

CellTuple& CellTuple::copy(const CellTuple& _cellTuple)
{
    f = _cellTuple.f;
    g = _cellTuple.g;
    h = _cellTuple.h;
    r = _cellTuple.r;
    c = _cellTuple.c;
    parent = _cellTuple.parent;

    return *this;
}
