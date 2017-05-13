#ifndef JSHAPE_H
#define JSHAPE_H

#include "public.h"
#include "shape.h"
#include "board.h"

class jshape : public shape
{
public:
    jshape(cell &, board &);
    ~jshape();

private:
    virtual void compute_rotate_positions() override;
};

#endif // JSHAPE_H
