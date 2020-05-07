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
    Street(QString name, Coordinate start, Coordinate end);
    Coordinate getStart();
    Coordinate getEnd();
    void insertStop(Stop stop);
    void writeList();

private:
    Coordinate start;
    Coordinate end;
    QString name;
    QVector<Coordinate> stopList;

};

#endif // STREET_H
