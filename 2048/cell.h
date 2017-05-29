#ifndef CELL_H
#define CELL_H

#include "public.h"

class cell
{
public:
    cell() { }
    cell(const QPoint&, const QPointF&, int);
    cell(int, int, float, float, int);
    cell(const QPoint&, float, float, int);
    cell(int, int, const QPointF&, int);

    cell(const cell& _cell) { copy(_cell); }
    cell& operator=(const cell& _cell) { return copy(_cell); }

    ~cell();

    const QPointF& get_position() const { return position; }
    const  QPoint& get_location() const { return location; }
    const QColor& get_color() const { return color; }
    QPointF& get_position() { return position; }
    QPoint& get_location() { return location; }
    QColor& get_color() { return color; }
    int get_number() const { return number; }

    void set_number_and_color(int num) { number = num; color = compute_color(); }

private:
    const QColor compute_color();
    float logrithm(float x, float y);
    cell& copy(const cell&);
    QPointF position;
    QPoint location;
    QColor color;
    int number;
};

#endif // CELL_H
