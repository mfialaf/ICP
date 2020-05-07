#ifndef STREET_H
#define STREET_H

#include <coordinate.h>
#include <QString>

class Street
{
public:

    Street();
    Street(Coordinate startC, Coordinate endC, QString nameC);
    Coordinate getStart();

private:
    Coordinate start;
    Coordinate end;
    QString name;

};

#endif // STREET_H
