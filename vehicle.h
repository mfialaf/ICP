#include <coordinate.h>
#include <path.h>
#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QDebug>

#ifndef VEHICLE_H
#define VEHICLE_H


class Vehicle
{

public:
    Vehicle();
    Vehicle(Coordinate position, double speed, Path path);
    QGraphicsEllipseItem* getEllipse();
    void vehMove(Coordinate coordinate);
    void vehUpdate();
    QGraphicsEllipseItem *visual;
    bool direction = true; //promenna pro zpetnou cestu, pri false vime ze jede na zpatek

private:
    Coordinate position;
    double speed;
    double distance = 0;
    Path path;


};



#endif // VEHICLE_H
