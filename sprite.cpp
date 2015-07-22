#include "sprite.h"
#include <iostream>

Sprite::Sprite()
{
    origTexture = true;
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
    mImage[0] = image;
    mTexture[0] = new QOpenGLTexture(image);
    mTexture[0]->setWrapMode(QOpenGLTexture::Repeat);

    mWidth = mTexture[0]->width();
    mHeight = mTexture[0]->height();
    mHotspot = Coordinate(mWidth/2, mHeight/2);
}

Sprite::Sprite(QImage &image, int w, int h) : Sprite()
{
    mImage[0] = image;
    mTexture[0] = new QOpenGLTexture(image);
    mTexture[0]->setWrapMode(QOpenGLTexture::Repeat);

    mWidth = w;
    mHeight = h;
    mHotspot = Coordinate(mWidth/2, mHeight/2);
}

size_t Sprite::genSubimg(unsigned int rows, unsigned int columns, unsigned int xsep, unsigned int ysep)
{

    mSubimg.clear();

    float w = mTexture[0]->width() / columns - xsep * 2;
    float h = mTexture[0]->height() / rows - ysep * 2;

    QSize size(w, h);

    for(size_t i = 0; i < rows; i++) {
        for(size_t j = 0; j < columns; j++) {
            QPoint coord(w * j + xsep * (2 * j + 1), h * i + ysep * (2 * i + 1));
            QRect rect = QRect(coord, size);

            QImage img = mImage[!origTexture].copy(rect);
            QOpenGLTexture *texture = new QOpenGLTexture(img);

            mSubimg.append(qMakePair(img, texture));
        }
    }

    return mSubimg.size()-1;
}

size_t Sprite::count()
{
    return mSubimg.size()-1;
}

void Sprite::setOrigTexture(bool value)
{
    origTexture = value;
}

void Sprite::setAlpha(const QColor &color)
{
    mImage[1] = mImage[0].convertToFormat(QImage::Format_ARGB32);
    for (int x=0; x < mImage[0].width(); ++x)
    {
        for (int y=0; y < mImage[0].height(); ++y)
        {
            QColor p = mImage[0].pixel(x,y);
            if (p == color)
                mImage[1].setPixel(x,y, Qt::transparent);
        }
    }
    mTexture[1] = new QOpenGLTexture(mImage[1]);
    origTexture = false;
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

    mTexture[!origTexture]->bind();

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex2f( -mHotspot.rx(), -mHotspot.ry() );

    glTexCoord2f(width()/mTexture[0]->width(), 0);
    glVertex2f( mWidth-mHotspot.rx(), -mHotspot.ry() );

    glTexCoord2f(width()/mTexture[0]->width(), height()/mTexture[0]->height());
    glVertex2f( mWidth-mHotspot.rx(), mHeight-mHotspot.ry() );

    glTexCoord2f(0, height()/mTexture[0]->height());
    glVertex2f( -mHotspot.rx(), mHeight-mHotspot.ry() );

    glEnd();

    glDisable(GL_BLEND);

}

void Sprite::render(int subimg)
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

    mSubimg[subimg].second->bind();

    QSize size = QSize(mSubimg[subimg].first.width(), mSubimg[subimg].first.height());
    QPoint center = QPoint(size.width()/2, size.height()/2);

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex2f( -center.rx(), -center.ry() );

    glTexCoord2f(1, 0);
    glVertex2f(size.width()-center.rx(), -center.ry());

    glTexCoord2f(1, 1);
    glVertex2f(size.width()-center.rx(), size.height()-center.ry());

    glTexCoord2f(0, 1);
    glVertex2f(-center.rx(), size.height()-center.ry() );

    glEnd();

    glDisable(GL_BLEND);
}

