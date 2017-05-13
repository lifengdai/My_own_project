#ifndef LSHAPE_H
#define LSHAPE_H

#include "public.h"
#include "shape.h"
#include "board.h"

class lshape : public shape
{
public:
    lshape(cell &, board &);
    ~lshape();

private:
    virtual void compute_rotate_positions() override;
};

#endif // LSHAPE_H
