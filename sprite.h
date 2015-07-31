#ifndef SPRITE_H
#define SPRITE_H

#include "coordinate.h"
#include <QOpenGLTexture>
#include <QSharedPointer>
#include <QOpenGLContext>

//#include "canvas.h"

class Canvas;
class Sprite;
class SubImage;

typedef QSharedPointer<Sprite> SpritePtr;
typedef QSharedPointer<SubImage> SubImagePtr;

class SubImage
{
public:
    SubImage(QImage image);

    QImage img;
    QSharedPointer<QOpenGLTexture> tex;

};

class Sprite
{
public:

    SubImagePtr mTexture[2];

    Sprite();
    Sprite(QImage &image);
    Sprite(QImage &image, int w, int h);

    void setAlpha(const QColor &color);
    void setFlip(bool x, bool y);
    void setSize(int w, int h);
    void move(int x, int y);
    void setHotspot(int x, int y);
    void scale(float x, float y);
    void scale(float scale);
    void render();
    void render(int subimg);
    void rotate(int angle);
    void setOrigTexture(bool value);
    size_t genSubimg(unsigned int rows, unsigned int columns, unsigned int xsep, unsigned int ysep);
    size_t count();

    int width() const;
    int height() const;

    void cleanup();

    Coordinate hotspot() const;
    QList<SubImagePtr> mSubimg;

private:

    Coordinate mPosition;
    Coordinate mHotspot;
    int mAngle;

    float xscale;
    float yscale;

    bool origTexture;
    QImage mImage[2];

    bool xflip;
    bool yflip;

    int xOff;
    int yOff;

    int mWidth;
    int mHeight;

};

#endif // SPRITE_H
