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

    void setFlip(bool x, bool y);
    void setSize(int w, int h);
    void move(int x, int y);
    void setHotspot(int x, int y);
    void scale(float x, float y);
    void scale(float scale);
    void render();
    void rotate(int angle);

    int width() const;
    int height() const;

    Coordinate hotspot() const;

private:
    Coordinate mPosition;
    Coordinate mHotspot;
    int mAngle;

    float xscale;
    float yscale;

    QOpenGLTexture *mTexture;

    bool xflip;
    bool yflip;

    int xOff;
    int yOff;

    int mWidth;
    int mHeight;

};

#endif // SPRITE_H
