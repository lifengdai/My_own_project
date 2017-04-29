#ifndef CELL_H
#define CELL_H

#include "public.h"

class cell
{
public:
    cell(const QPointF &_point, const QPoint &_position, int _color = 0);
    cell() {}
    cell(const cell& _cell) { copy(_cell); }
    static float length;
    QColor draw_cell_color() const;
    const QPointF& get_point() const { return point; }
    const QPoint& get_position() const { return position; }
    int get_length() const { return length; }
    int get_color() const { return color; }
    void  set_color(int _color) { color = _color; }
    void set_real_color(int _color) { real_color = _color; }
    int get_real_color() { return real_color; }
    cell& operator=(const cell& _cell) { return copy(_cell); }
    ~cell();
private:
    cell& copy(const cell& _cell);
    QPointF point;
    QPoint position;
    int color;
    int real_color;
};

#endif // CELL_H
