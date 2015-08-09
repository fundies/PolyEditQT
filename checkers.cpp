#include "checkers.h"

QImage createCheckers()
{
    //creates a checker pattern

    quint32 width = 64;
    quint32 height = width;
    quint32 checkCount = 8;
    quint32 checkSize = width / checkCount;

    quint32 i = 0;
    bool light = true;

    uchar *data = new uchar[width * height * 4];

    for (quint32 j = 0; j < checkCount; ++j)
    {
        for (quint32 k = 0; k < checkCount; ++k)
        {
            for (quint32 l = 0; l < checkSize; ++l)
            {
                for (quint32 m = 0; m < checkSize; ++m)
                {
                    if (light)
                    {
                        data[i++] = 179u;
                        data[i++] = 179u;
                        data[i++] = 179u;
                        data[i++] = 255u;
                    }
                    else
                    {
                        data[i++] = 230u;
                        data[i++] = 230u;
                        data[i++] = 230u;
                        data[i++] = 255u;
                    }
                }
                light = !light;
            }
        }
        light = !light;
    }

    QImage c = QImage(data, width, height, QImage::Format_RGB32);
    return c;
}

