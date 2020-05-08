#ifndef STOP_H
#define STOP_H

#include <QString>
#include <coordinate.h>

class Stop
{
public:
    Stop();
    Stop(QString name, Coordinate position);
//    void setStreet(Street street);
    Coordinate getPosition();
    QString getName();

private:
    QString name;
    Coordinate position;
//    Street street;
};

#endif // STOP_H
