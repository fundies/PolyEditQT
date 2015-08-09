#ifndef SHAPES_H
#define SHAPES_H

#include <QString>

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


#endif // SHAPES_H

