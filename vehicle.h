#include <coordinate.h>
#include <path.h>
//#include <QGraphicsEllipseItem>
#include <QtWidgets>

#ifndef VEHICLE_H
#define VEHICLE_H


class Vehicle
{
public:
    Vehicle();
    Vehicle(Coordinate position, double speed, Path path);

private:
    Coordinate position;
    double speed;
    double distance = 0;
    Path path;
//    QList<QGraphicsEllipseItem> gui;
};



#endif // VEHICLE_H
