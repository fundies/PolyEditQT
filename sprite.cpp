#include "sprite.h"
#include <iostream>

Sprite::Sprite()
{
    mPosition = Coordinate(0,0);

    mAngle=0;

    xscale=1;
    yscale=1;

    xflip=false;
    yflip=false;

    xOff = 0;
    yOff = 0;

}

Sprite::Sprite(QImage &image) : Sprite()
{
    mTexture = new QOpenGLTexture(image);
    mTexture->setWrapMode(QOpenGLTexture::Repeat);

    mWidth = mTexture->width();
    mHeight = mTexture->height();
    mHotspot = Coordinate(mWidth/2, mHeight/2);
}

Sprite::Sprite(QImage &image, int w, int h) : Sprite()
{
    mTexture = new QOpenGLTexture(image);
    mTexture->setWrapMode(QOpenGLTexture::Repeat);

    mWidth = w;
    mHeight = h;
    mHotspot = Coordinate(mWidth/2, mHeight/2);
}

void Sprite::setFlip(bool x, bool y)
{
    xflip=x;
    yflip=y;
}

void Sprite::setHotspot(int x, int y)
{
    mHotspot.setX(x);
    mHotspot.setY(y);
}

void Sprite::move(int x, int y)
{
    mPosition.setX(x);
    mPosition.setY(y);
}

void Sprite::scale(float x, float y)
{
    xscale=x;
    yscale=y;
}

void Sprite::scale(float scale)
{
    xscale=scale;
    yscale=scale;
}

void Sprite::setSize(int w, int h)
{
    mWidth = w;
    mHeight = h;
    mHotspot = Coordinate(mWidth/2, mHeight/2);
}

void Sprite::rotate(int angle)
{
    mAngle=angle;
}
int Sprite::width() const
{
    return mWidth;
}
int Sprite::height() const
{
    return mHeight;
}
Coordinate Sprite::hotspot() const
{
    return mHotspot;
}


void Sprite::render()
{

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if(xscale!=1 || yscale!=1)
    {
        glScalef(xscale, yscale, 1);
    }

    if(mAngle!=0)
    {
        glRotatef(mAngle, 0,0,1);
    }

    mTexture->bind();

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex2f( -mHotspot.rx(), -mHotspot.ry() );

    glTexCoord2f(width()/mTexture->width(), 0);
    glVertex2f( mWidth-mHotspot.rx(), -mHotspot.ry() );

    glTexCoord2f(width()/mTexture->width(), height()/mTexture->height());
    glVertex2f( mWidth-mHotspot.rx(), mHeight-mHotspot.ry() );

    glTexCoord2f(0, height()/mTexture->height());
    glVertex2f( -mHotspot.rx(), mHeight-mHotspot.ry() );

    glEnd();

    glDisable(GL_BLEND);

}

