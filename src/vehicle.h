/**
  * @file vehicle.h
  * @authors Daniel Kamenický xkamen21
  * <br/>Marek Fiala xfiala60
  * @details Hlavičkový modul k modulu vehicle.cpp
  */

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
    Vehicle(Coordinate position, double speed, Path path, int color);
    QGraphicsEllipseItem* getEllipse();
    void vehMove(Coordinate coordinate);
    void vehUpdate(int hours);
    bool direction = true; //promenna pro zpetnou cestu, pri false vime ze jede na zpatek
    Path getPath();
    double getDistance();
    bool isAtStart();
    bool compareWithTollerance(double a, double b);

private:
    Coordinate position;
    double speed;
    double distance = 0;
    Path path;
    int stopWaiter = 0;
    QGraphicsEllipseItem *visual;
    int countWait = 0;
    int EndPathWaiter = 0;


};



#endif // VEHICLE_H
