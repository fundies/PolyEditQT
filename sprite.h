#ifndef SPRITE_H
#define SPRITE_H

#include "coordinate.h"
#include <QOpenGLTexture>

class Sprite
{
public:

    Sprite(QImage &image);

    //Grid boxes;
    //void setBoxBounds(unsigned int rows, unsigned int columns, unsigned int xsep, unsigned int ysep);

    void setFlip(bool x, bool y);
    void move(int x, int y);
    void setHotspot(int x, int y);
    void scale(float x, float y);
    void scale(float scale);
    //void setImage(std::shared_ptr<Image> &image);
    void render();
    void rotate(int angle);

    //const wxSize getSize();
    //const wxSize getTextureSize();

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
    int width;
    int height;

};

#endif // SPRITE_H
