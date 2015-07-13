#include "coordinate.h"

Coordinate::Coordinate() : QPoint()
{
    mColor = Qt::white;
}

Coordinate::Coordinate(int x, int y, QColor color) : QPoint(x,y)
{
    mColor = color;
}

Coordinate::Coordinate(int x, int y) : QPoint(x,y)
{
    Coordinate();
}

Coordinate::Coordinate(QPoint p) : QPoint(p.rx(), p.ry())
{
    Coordinate();
}

Coordinate::Coordinate(QPoint p, QColor color) : QPoint(p.rx(), p.ry())
{
    mColor = color;
}

QColor Coordinate::color() const
{
    return mColor;
}

void Coordinate::setColor(const QColor &color)
{
    mColor = color;
}


