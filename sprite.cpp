#include <QOpenGLContext>

#include "sprite.h"
#include "canvas.h"
#include "utility.h"

SubImage::SubImage()
{
}

SubImage::SubImage(QImage image)
{
    tex = QSharedPointer<QOpenGLTexture>(new QOpenGLTexture(image));
    img = image;
}

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
    mTexture[0] = SubImage(image);

    mWidth = image.width();
    mHeight = image.height();
    mHotspot = Coordinate(mWidth/2, mHeight/2);
}

Sprite::Sprite(QImage &image, int w, int h) : Sprite()
{
    mImage[0] = image;
    mTexture[0] = SubImage(image);

    mWidth = w;
    mHeight = h;
    mHotspot = Coordinate(mWidth/2, mHeight/2);
}

size_t Sprite::genSubimg(unsigned int rows, unsigned int columns, unsigned int xsep, unsigned int ysep)
{

    mRows = rows;
    mColumns = columns;

    mSubimg.clear();

    float w = mImage[0].width() / columns - xsep * 2;
    float h = mImage[0].height() / rows - ysep * 2;

    QSize size(w, h);

    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < columns; j++)
        {
            QPoint coord(w * j + xsep * (2 * j + 1), h * i + ysep * (2 * i + 1));
            QRect rect = QRect(coord, size);

            QImage img = mImage[!origTexture].copy(rect);
            mSubimg.append(SubImage(SubImage(img)));
        }
    }

    return mSubimg.size();
}

size_t Sprite::count()
{
    return mSubimg.size();
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
    mTexture[1] = SubImage(mImage[1]);
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
int Sprite::rows() const
{
    return mRows;
}
int Sprite::columns() const
{
    return mColumns;
}

void Sprite::render()
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if(xscale!=1 || yscale!=1)
        glScalef(xscale, yscale, 1);

    if(mAngle!=0)
        glRotatef(mAngle, 0,0,1);

    mTexture[!origTexture].tex->bind();

    glBegin(GL_QUADS);

    glTexCoord2f(0, 0);
    glVertex2f( -mHotspot.rx(), -mHotspot.ry() );

    glTexCoord2f(width()/mTexture[0].tex->width(), 0);
    glVertex2f( mWidth-mHotspot.rx(), -mHotspot.ry() );

    glTexCoord2f(width()/mTexture[0].tex->width(), height()/mTexture[0].tex->height());
    glVertex2f( mWidth-mHotspot.rx(), mHeight-mHotspot.ry() );

    glTexCoord2f(0, height()/mTexture[0].tex->height());
    glVertex2f( -mHotspot.rx(), mHeight-mHotspot.ry() );

    glEnd();

    glDisable(GL_TEXTURE_2D);

    // Reset to white
    glColor4f(1,1,1,1);

}

void Sprite::render(int subimg)
{

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if(xscale!=1 || yscale!=1)
        glScalef(xscale, yscale, 1);

    if(mAngle!=0)
        glRotatef(mAngle, 0,0,1);

    mSubimg[subimg].tex->bind();

    QSize size = QSize(mSubimg[subimg].img.width(), mSubimg[subimg].img.height());
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

    glDisable(GL_TEXTURE_2D);

    // Reset to white
    glColor4f(1,1,1,1);


}

bool Sprite::isNull()
{
    return mSubimg.isEmpty();
}

Sprite::Sprite(const Sprite &other)
{

    mPosition = other.mPosition;
    mHotspot = other.mHotspot;
    mAngle = 0;
    xscale = 1;
    yscale = 1;

    origTexture = other.origTexture;
    mImage[0] = other.mImage[0];
    mImage[1] = other.mImage[1];

    xflip = other.xflip;
    yflip = other.yflip;

    xOff = other.xOff;
    yOff = other.yOff;

    mWidth = other.mWidth;
    mHeight = other.mHeight;

    mSubimg.clear();
    for (int i=0; i < other.mSubimg.size(); ++i)
        mSubimg.append(SubImage(other.mSubimg[i].img));
}

void Sprite::exportStrip(QString fpath)
{
    QImage img = generateStrip();
    img.save(fpath);
}

QImage Sprite::generateStrip()
{
    int columns = std::max(getFactor(count()), 1);
    int rows = count()/columns;

    mRows = columns;
    mColumns = rows;

    int w = mSubimg.first().img.width();
    int h = mSubimg.first().img.height();

    int width = rows * w;
    int height = columns * h;


    QImage img(width, height, QImage::Format_ARGB32);
    img.fill(Qt::transparent);

    int r = 0;
    int c = 0;
    for (auto i : mSubimg)
    {
        for (int x=0; x < i.img.width(); ++x)
        {
            for (int y=0; y < i.img.height(); ++y)
            {
                QRgb p = i.img.pixel(x,y);
                img.setPixel((r * w) + x, (c * h) + y, p);
            }
        }

        if (r < rows-1)
            r++;
        else
        {
            c++;
            r = 0;
        }
    }

    return img;
}
