#include "cell.h"

cell::cell(const QPoint& _location, const QPointF& _position, int num)
{
    location = _location;
    position = _position;
    number = num;
    color = compute_color();
}

cell::cell(int r, int c, float x, float y, int num)
{
    location = QPoint(r, c);
    position = QPointF(x, y);
    number = num;
    color = compute_color();
}

cell::cell(const QPoint& _location, float x, float y, int num)
{
    location = _location;
    position = QPointF(x, y);
    number = num;
    color = compute_color();
}

cell::cell(int r, int c, const QPointF& _position, int num)
{
    location = QPoint(r, c);
    position = _position;
    number = num;
    color = compute_color();
}

cell& cell::copy(const cell& _cell)
{
    position = _cell.position;
    location = _cell.location;
    color = _cell.color;
    number = _cell.number;

    return *this;
}

const QColor cell::compute_color()
{
    int index = 0;

    if(number > EMPTY)
    {
        index = logrithm(LOG_BASE, number);
    }

    return colors[index];
}

float cell::logrithm(float base, float number)
{
    return qLn(number) / qLn(base);
}

cell::~cell()
{

}
