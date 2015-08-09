#ifndef SPRITE_H
#define SPRITE_H

#include <QOpenGLTexture>
#include <QSharedPointer>
#include <QOpenGLContext>

#include "coordinate.h"

class Canvas;

/**
 * @brief The SubImage class
 */
class SubImage
{
public:

    /**
     * @brief SubImage constructor
     */
    SubImage();

    /**
     * @brief SubImage constructor
     * @param image image
     */
    SubImage(QImage image);

    QImage img;
    QSharedPointer<QOpenGLTexture> tex;

};

/**
 * @brief The Sprite class
 */
class Sprite
{
public:

    /**
     * @brief Sprite constructor
     */
    Sprite();

    /**
     * @brief Sprite constructor
     * @param image image
     */
    Sprite(QImage &image);

    /**
     * @brief Sprite constructor
     * @param image image
     * @param w width
     * @param h height
     */
    Sprite(QImage &image, int w, int h);

    /**
     * @brief Sprite copy constructor
     * @param other source
     */
    Sprite(const Sprite &other);

    /**
     * @brief setAlpha sets color to alpha
     * @param color source color
     */
    void setAlpha(const QColor &color);

    /**
     * @brief setFlip mirror the sprite
     * @param x xflip
     * @param y yflip
     */
    void setFlip(bool x, bool y);

    /**
     * @brief setSize resize the sprite
     * @param w width
     * @param h height
     */
    void setSize(int w, int h);

    /**
     * @brief move position the sprite
     * @param x x position
     * @param y y position
     */
    void move(int x, int y);

    /**
     * @brief setHotspot sets the sprite origin
     * @param x x coordinate
     * @param y y corrdinate
     */
    void setHotspot(int x, int y);

    /**
     * @brief scale set the scale
     * @param x xscale
     * @param y yscale
     */
    void scale(float x, float y);

    /**
     * @brief scale set the scale
     * @param scale scale
     */
    void scale(float scale);

    /**
     * @brief render draw the sprite
     */
    void render();

    /**
     * @brief render draw the sprite's subimage
     * @param subimg subimage
     */
    void render(int subimg);

    /**
     * @brief rotate sets the sprite's rotation
     * @param angle rotation
     */
    void rotate(int angle);

    /**
     * @brief setOrigTexture removes the alpha
     * @param value true/false
     */
    void setOrigTexture(bool value);

    /**
     * @brief genSubimg cuts the sheet into images
     * @param rows rows
     * @param columns columns
     * @param xsep horizontal seperation
     * @param ysep vertical seperation
     * @return number of images
     */
    size_t genSubimg(unsigned int rows, unsigned int columns, unsigned int xsep, unsigned int ysep);

    /**
     * @brief count
     * @return number of subimages
     */
    size_t count();

    /**
     * @brief exportStrip exports sprite as strip
     * @param fpath file path
     */
    void exportStrip(QString fpath);

    /**
     * @brief generateStrip generates sprite as strip
     * @return image
     *
     */
    QImage generateStrip();

    /**
     * @brief width get width
     * @return width
     */
    int width() const;

    /**
     * @brief height get height
     * @return height
     */
    int height() const;

    /**
     * @brief isNull checks is subimage vector empty
     * @return true/false
     */
    bool isNull();

    /**
     * @brief hotspot gets the origin
     * @return origin
     */
    Coordinate hotspot() const;

    /**
     * @brief rows get number of rows
     * @return rows
     */
    int rows() const;

    /**
     * @brief columns get number of columns
     * @return columns
     */
    int columns() const;

    QList<SubImage> mSubimg;

private:

    QImage mImage[2];
    Coordinate mPosition;
    Coordinate mHotspot;
    SubImage mTexture[2];
    int mAngle;
    float xscale;
    float yscale;
    bool origTexture;
    bool xflip;
    bool yflip;
    int xOff;
    int yOff;
    int mWidth;
    int mHeight;
    int mRows;
    int mColumns;
};

typedef Sprite *SpritePtr;

#endif // SPRITE_H
