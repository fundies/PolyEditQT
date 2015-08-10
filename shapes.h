#ifndef SHAPES_H
#define SHAPES_H

#include <QString>
#include <QOpenGLFunctions>

#include "coordinate.h"

/**
 * Shapes enum
 */
namespace PolyEdit
{
    typedef enum Shape
    {
        Polygon = 0,
        Circle = 1,
        Box = 2,
        Invalid = -1
    } Shape;

    /**
     * @brief hashit converts string to shape type
     * @param inString string
     * @return  shape
     */
    Shape hashit (QString const &inString);
}

class Circle : protected QOpenGLFunctions
{
public:

    /**
     * @brief drawCircle draw a circle
     * @param c center
     * @param radius raidius
     * @param steps steps
     * @param outline outline or fill
     */
    static void drawCircle(Coordinate c, int radius, int steps, bool outline);
};

#endif // SHAPES_H

