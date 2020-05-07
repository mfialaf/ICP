#ifndef STOP_H
#define STOP_H

#include <QString>
#include <street.h>
#include <coordinate.h>

class Stop
{
public:
    Stop();
    Stop(QString name, Coordinate position);
//    void setStreet(Street street);
    Coordinate getPosition();

private:
    QString name;
    Coordinate position;
//    Street street;
};

#endif // STOP_H
