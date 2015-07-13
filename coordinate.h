#ifndef COORDINATE_H
#define COORDINATE_H

#include <QPoint>
#include <QColor>

/**
 * @brief Override of QPoint class with color added
 */
class Coordinate : public QPoint
{
public:
    /**
     * @brief Coordinate Default constructor
     */
    Coordinate();

    /**
     * @brief Coordinate
     * @param x x
     * @param y y
     */
    Coordinate(int x, int y);

    /**
     * @brief Coordinate
     * @param x x
     * @param y y
     * @param color
     */
    Coordinate(int x, int y, QColor color);

    /**
     * @brief Coordinate
     * @param p c
     */
    Coordinate(QPoint p);

    /**
     * @brief Coordinate
     * @param p c
     * @param color
     */
    Coordinate(QPoint p, QColor color);

    /**
     * @brief color Returns Coordinate's color
     * @return color color
     */
    QColor color() const;

    /**
     * @brief setColor Set Coordinate's color
     * @param color new color
     */
    void setColor(const QColor &color);

private:

    QColor mColor;
};

#endif // COORDINATE_H
