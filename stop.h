#ifndef STOP_H
#define STOP_H

#include <QString>
#include <coordinate.h>

class Stop
{
public:
    Stop();
    Stop(QString name, Coordinate position);
    Coordinate getPosition();
    QString getName();

private:
    QString name;
    Coordinate position;
};

#endif // STOP_H
