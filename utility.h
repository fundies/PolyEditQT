#ifndef UTILITY_H
#define UTILITY_H

#include "coordinate.h"

/**
 * @brief random_string generates random string
 * @param length length of string
 * @return string
 */
QString random_string(size_t length);

/**
 * @brief getFactor get factor of number
 * @param number number
 * @return factor
 */
int getFactor(int number);

/**
 * @brief compareDouble avoids warnings for compairing doubles
 * @param a a
 * @param b b
 * @return a==b
 */
bool compareDouble(double a, double b);

/**
 * @brief distance distance between two points
 * @param c1 coordinate 1
 * @param c2 coordinate 2
 * @return distance
 */
int distance(Coordinate c1, Coordinate c2);

template<typename T>
/**
 * @brief RoundNum round to the nearest multiple
 * @param value vale
 * @param multiple multiple
 * @return rounded
 */
T RoundNum( T value, T multiple )
{
    if (compareDouble(multiple,0)) return value;
    return static_cast<T>(std::round(static_cast<double>(value)/static_cast<double>(multiple))*static_cast<double>(multiple));
}

template <typename T>
/**
 * @brief sign return sign of a number
 * @param value
 * @return sign
 */
int sign(T value)
{
    return (T(0) < value) - (value < T(0));
}

#endif // UTILITY_H
