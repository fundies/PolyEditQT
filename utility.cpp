#include "utility.h"
#include <QGLWidget>

QString random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ rand() % max_index ];
    };
    QString str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

bool isPrime(int number)
{
    if(number < 2)
        return false;

    if(number == 2)
        return true;

    if(number % 2 == 0)
        return false;

    for(int i=3; (i*i)<=number; i+=2)
    {
        if(number % i == 0 )
            return false;
    }

    return true;

}

int getFactor(int number)
{
    int result = 0;
    int dist = number;
    int root = sqrt(number) + 1;

    for (int i = 1; i < root; i++)
    {
        if (number % i == 0)
        {
            int tempDis = (root - i);
            if (tempDis < dist)
                result = i;
        }
    }
    return result;
}

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

    for (int i = 0; i <= steps; i++)
        glVertex2f(x + cos(i * M_PI * 2 / steps) * radius, y - sin(i * M_PI * 2 / steps) * radius);

    glEnd();
}

int distance(Coordinate c1, Coordinate c2)
{
    return sqrt(pow((c2.rx()-c1.rx()),2) + pow((c2.ry()-c1.ry()),2));
}
