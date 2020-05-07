#include "vehicle.h"

Vehicle::Vehicle(QObject *parent) :
    QGraphicsScene(parent)
{

}

Vehicle::Vehicle(Coordinate position, double speed, Path path)
{
    this->position = position;
    this->speed = speed;
    this->path = path;
//    this->mark = scene->addEllipse()
}
