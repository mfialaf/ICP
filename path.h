#ifndef PATH_H
#define PATH_H

#include <QList>
#include <coordinate.h>

class Path
{
public:
    Path();
    Path(QList<Coordinate> pathList);

    double getDistanceOfCoordinates(Coordinate a, Coordinate b);
    Coordinate getCoordinateByDistance (double distance, bool direction);
    double getPathValue();


private:
    QList<Coordinate> pathList;
    QVector<Coordinate> stopList;
};

#endif // PATH_H
