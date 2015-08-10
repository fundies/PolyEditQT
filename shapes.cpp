#include "shapes.h"

#ifndef M_PI
    #define M_PI 3.14159265359
#endif

namespace PolyEdit
{
    Shape hashit (QString const &inString)
    {
        if (inString == "polyline") return Polygon;
        if (inString == "circle") return Circle;
        if (inString == "rect") return Box;
        return Invalid;
    }
}

void Circle::drawCircle(Coordinate c, int radius, int steps, bool outline)
{
    int x = c.rx();
    int y = c.ry();

    if (!outline)
    {
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
    }
    else
        glBegin(GL_LINE_LOOP);

    for (int i = 0; i <= steps; i++)
        glVertex2f(x + cos(i * M_PI * 2 / steps) * radius, y - sin(i * M_PI * 2 / steps) * radius);

    glEnd();
}
