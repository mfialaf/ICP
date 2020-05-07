#ifndef STREET_H
#define STREET_H

#include <coordinate.h>
#include <QString>
#include <QVector>
#include <stop.h>

class Street
{
public:

    Street();
    Street(Coordinate start, Coordinate end, QString name);
    Coordinate getStart();
    Coordinate getEnd();
    void insertStop(Stop stop);

private:
    Coordinate start;
    Coordinate end;
    QString name;
    QVector<Coordinate> stopList;

};

#endif // STREET_H
