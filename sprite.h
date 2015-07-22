#ifndef SPRITE_H
#define SPRITE_H

#include "coordinate.h"
#include <QOpenGLTexture>

class Sprite
{
public:

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

    Coordinate hotspot() const;

private:
    Coordinate mPosition;
    Coordinate mHotspot;
    int mAngle;

    float xscale;
    float yscale;

    bool origTexture;
    QOpenGLTexture *mTexture[2];
    QImage mImage[2];

    QList<QPair<QImage, QOpenGLTexture*>> mSubimg;

    bool xflip;
    bool yflip;

    int xOff;
    int yOff;

    int mWidth;
    int mHeight;

};

#endif // SPRITE_H
