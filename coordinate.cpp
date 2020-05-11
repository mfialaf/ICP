#include "coordinate.h"

/**
 * @brief Coordinate::Coordinate konstruktor
 * @param x
 * @param y
 */
Coordinate::Coordinate(double x, double y)
{
    this->x = x;
    this->y = y;
}

/**
 * @brief Coordinate::Coordinate konstruktor
 */
Coordinate::Coordinate(){}

/**
 * @brief Coordinate::setX Nastaví souřadnici x
 * @param x souřadnice
 */
void Coordinate::setX(double x)
{
    this->x = x;
}

/**
 * @brief Coordinate::setY Nastaví souřadnici y
 * @param y souřadnice
 */
void Coordinate::setY(double y)
{
    this->y = y;
}

/**
 * @brief Coordinate::getX
 * @return Vrátí souřadnici x
 */
double Coordinate::getX()
{
    return this->x;
}

/**
 * @brief Coordinate::getY
 * @return Vrátí souřadnici y
 */
double Coordinate::getY()
{
    return this->y;
}
