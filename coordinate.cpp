/** @brief Imitace dopravních spojů.

    Semestrální projekt - aplikace pro zobrazení linek hromadné dopravy a sledování jejich pohybu.
    @authors Daniel Kamenický xkamen21 & Marek Fiala xfiala60
    @date Květen 2020
    @sub ICP Seminář C++
*/

#include "coordinate.h"
/*
Coordinate::Coordinate(QWidget *parent) : QWidget(parent)
{

}*/

Coordinate::Coordinate(double x, double y)
{
    this->x = x;
    this->y = y;
}

Coordinate::Coordinate(){}

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
