#ifndef MASK_H
#define MASK_H

#include <QList>
#include <QOpenGLWidget>

#include "coordinate.h"
#include "shapes.h"

/**
 * @brief The Mask class
 */
class Mask
{
public:
    /**
     * @brief Mask Constructor
     * @param parent parent
     */
    Mask(QOpenGLWidget *parent);

    /**
     * @brief addc add c
     * @param c new c
     */
    void addc(Coordinate c);

    /**
     * @brief replace replace c
     * @param index index to replace
     * @param c new c
     */
    void replace(int index, Coordinate c);

    /**
     * @brief deletec delete a c
     * @param index index to delete
     */
    void deletec(int index);

    /**
     * @brief render draw
     */
    void render();

    /**
     * @brief render render a temporary shape based on mouse's position
     * @param mousePos mouse position
     */
    void render(Coordinate mousePos);

    /**
     * @brief clear clear all vertecies
     */
    void clear();

    /**
     * @brief size returns number of vertecies
     * @return number of vertecies
     */
    int size();

    /**
     * @brief setCircle set the mask type to circle
     * @param origin origin
     * @param radius radius
     */
    void setCircle(Coordinate origin, int mRadius);

    /**
     * @brief setBox set mask type to box
     * @param left left
     * @param top top
     * @param width width
     * @param height height
     */
    void setBox(int left, int top, int width, int height);

    /**
     * @brief getc returns a coordinate st specified index
     * @param i index
     * @return coordinate[index]
     */
    const Coordinate &getc(int index) const;

    /**
     * @brief getRadius returns radius if type == circle
     * @return radius
     */
    int getRadius() const;

    /**
     * @brief setRadius set the radius used with circle masks only
     * @param value
     */
    void setRadius(int radius);

    /**
     * @brief setType set the type of mask
     * @param type Polygon, Circle, Box...
     */
    void setType(const PolyEdit::Shape &type);

    /**
     * @brief scale sets the scale
     * @param scale scale
     */
    void scale(float scale);

    /**
     * @brief scale sets the scale
     * @param x xscale
     * @param y yscale
     */
    void scale(float x, float y);

    /**
     * @brief exportSVG exports mask to SVG file
     * @param fpath file path
     */
    void exportSVG(QString fpath);

private:

    QList<Coordinate> mcs;
    QOpenGLWidget *mParent;
    PolyEdit::Shape mType;
    float xscale;
    float yscale;
    int mRadius;
};

#endif // MASK_H
