#ifndef PATH_H
#define PATH_H

#include <QList>
#include <coordinate.h>
#include <stop.h>

class Path
{
public:
    Path();
    Path(QList<Coordinate> pathList);
    Path(QVector<QString> streetNames, double speed, double linkNumber, double interval);

    double getDistanceOfCoordinates(Coordinate a, Coordinate b);
    Coordinate getCoordinateByDistance (double distance, bool direction);
    double getPathValue();


private:
    QList<Coordinate> pathList;
    QVector<Stop> stopList;
    QVector<QString> streetNames;
    double speed;
    double pathNumber;
    double interval;
};

#endif // PATH_H
