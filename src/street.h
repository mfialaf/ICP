/**
  * @file street.h
  * @authors Daniel Kamenický xkamen21
  * <br/>Marek Fiala xfiala60
  * @details Hlavičkový modul k modulu street.cpp
  */

#ifndef STREET_H
#define STREET_H

#include <coordinate.h>
#include <QString>
#include <QVector>
#include <stop.h>
#include <QGraphicsLineItem>
#include <QDebug>
#include <math.h>
#include <QPen>

class Street
{
public:
    Street();
    Street(QString name, Coordinate start, Coordinate end);
    Coordinate getStart();
    Coordinate getEnd();
    QString getName();
    void insertStop(Stop stop);
    void sortStops();
    double getDistanceFromStart(Coordinate coordinate);
    Stop getStopOnPosition(int position);
    int getSizeOfStopList();
    int getDelay();
    void setDelay(int delay);
    QGraphicsLineItem* getStreetAsQraphicsLine();

private:
    Coordinate start;
    Coordinate end;
    QString name;
    QVector<Stop> stopList;
    int delay = 0;
    QGraphicsLineItem* line;

};

#endif // STREET_H
