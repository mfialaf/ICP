#include "coordinate.h"
/*
Coordinate::Coordinate(QWidget *parent) : QWidget(parent)
{

}*/

Coordinate::Coordinate(){
    x = 0.0;
    y = 0.0;
}

void Coordinate::setX(double x)
{
    this->x = x;
}

void Coordinate::setY(double y)
{
    this->y = y;
}

double Coordinate::getX()
{
    return this->x;
}

double Coordinate::getY()
{
    return this->y;
}
