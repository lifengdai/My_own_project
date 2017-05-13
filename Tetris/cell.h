#ifndef CELL_H
#define CELL_H

#include "public.h"

class cell
{
public:
    cell() {}
    cell(QPoint &, QPointF &, int _color = NO_COLOR);
    cell(const cell& c) { copy(c); }
    cell& operator=(const cell& c) { return copy(c); }
    int get_color() { return color; }
    void set_color(int _color) { color = _color; }
    QPointF& get_position() { return position; }
    QPoint& get_location() { return location; }
    QColor draw_cell_color() const;
    ~cell();

private:
    QPointF position;
    QPoint location;
    cell& copy(const cell&);
    int color;
};

#endif // CELL_H
