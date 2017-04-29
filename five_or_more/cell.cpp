#include "cell.h"

float cell::length = 0.0f;

cell::cell(const QPointF& _point, const QPoint& _position, int _color)
    : point(_point), position(_position)
{
    color = _color;
    real_color = false;
}

QColor cell::draw_cell_color() const
{
    QColor qcolor;
    switch(color)
    {
    case RED:
        qcolor = QColor("red");
        break;
    case YELLOW:
        qcolor = QColor("yellow");
        break;
    case BLUE:
        qcolor = QColor("blue");
        break;
    case GRAY:
        qcolor = QColor("gray");
        break;
    case BLACK:
        qcolor = QColor("black");
        break;
    case PURPLE:
        qcolor = QColor("purple");
        break;
    case ORANGE:
        qcolor = QColor("orange");
        break;
    default:
        qcolor = QColor("transparent");
        break;
    }

    return qcolor;
}

cell& cell::copy(const cell& _cell)
{
    point = _cell.point;
    position = _cell.position;
    color = _cell.color;
    real_color = _cell.real_color;

    return *this;
}

cell::~cell()
{

}

