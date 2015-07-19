#include "sprite.h"
#include <iostream>

Sprite::Sprite(QImage &image)
{

    mPosition = Coordinate(0,0);

    mAngle=0;

    xscale=1;
    yscale=1;

    xflip=false;
    yflip=false;

    mTexture = new QOpenGLTexture(QImage("/home/greg/mario.png"));

    xOff = 0;
    yOff = 0;

    width = mTexture->width();
    height = mTexture->height();

    mHotspot = Coordinate(width/2, height/2);

    //fullRect = false;
    //subImg = 0;
    //Rows = 1;
    //Columns = 1;
    //Xsep = 0;
    //Ysep = 0;
    //m_image->Create(1,1,true);
    //boxes = Grid(0,0,1,1,0,0);
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

/*void Sprite::setImage(std::shared_ptr<Image> &image)
{
    image=std::move(image);
}*/

void Sprite::rotate(int angle)
{
    mAngle=angle;
}

void Sprite::render()
{
    //assert(image!=NULL);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    glLoadIdentity();

    glTranslatef(0,0,0);

    if(xscale!=1 || yscale!=1)
    {
        glScalef(xscale, yscale, 1);
    }

    if(mAngle!=0)
    {
        glRotatef(mAngle, 0,0,1);
    }

    //mTexture = new QOpenGLTexture(QImage("/home/greg/mario.png"));
    mTexture->bind();

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex2f(0, 0);

    glTexCoord2f(1, 0);
    glVertex2f(width, 0);

    glTexCoord2f(1, 1);
    glVertex2f(width, height);

    glTexCoord2f(0, 1);
    glVertex2f(0, height);

    glEnd();

}

/*void Sprite::setBoxBounds(unsigned int rows, unsigned int columns, unsigned int xsep, unsigned int ysep)
{
    unsigned int width = image->textureWidth;
    unsigned int height = image->textureHeight;
    boxes.setSize(width, height, rows, columns, xsep, ysep);
}

const wxSize Sprite::getTextureSize()
{
    return wxSize(image->textureWidth, image->textureHeight);
}*/

