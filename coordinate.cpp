#include "coordinate.h"

coordinate::coordinate(QWidget *parent) : QWidget(parent)
{

}

void coordinate::setX(double x)
{
    coordinates.x = x;
}

void coordinate::setY(double y)
{
    coordinates.y = y;
}

double coordinate::getX(double x)
{
    return coordinates.x;
}

double coordinate::getY(double y)
{
    return coordinates.y;
}
