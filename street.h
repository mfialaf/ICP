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
    QGraphicsLineItem* line;

private:
    Coordinate start;
    Coordinate end;
    QString name;
    QVector<Stop> stopList;
    int delay = 0;

};

#endif // STREET_H
