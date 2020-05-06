#include "coordinate.h"
/*
Coordinate::Coordinate(QWidget *parent) : QWidget(parent)
{

}*/

Coordinate::Coordinate(double x, double y){
    this->x = x;
    this->y = y;
}

<<<<<<< HEAD
Coordinate::Coordinate(double x, double y)
{
    this->x = x;
    this->y = y;
}
=======
Coordinate::Coordinate(){}
>>>>>>> e29ee25652fe3aa1874effeea5303d9c405df110

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
