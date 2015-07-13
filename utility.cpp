#include "utility.h"
#include <QGLWidget>

bool compareDouble(double a, double b)
{
     return std::fabs(a - b) < std::numeric_limits<double>::epsilon();
}

void drawCircle(Coordinate c, int radius, int steps, bool outline)
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

    for (int i = 0; i <= steps; i++) {
     glVertex2f(x + cos(i * M_PI * 2 / steps) * radius, y - sin(i * M_PI * 2 / steps) * radius);
    }

    glEnd();
}

int distance(Coordinate c1, Coordinate c2)
{
    return sqrt(pow((c2.rx()-c1.rx()),2) + pow((c2.ry()-c1.ry()),2));
}
