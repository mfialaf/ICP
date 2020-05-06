#ifndef PATH_H
#define PATH_H

#include <QList>
#include <coordinate.h>

class Path
{
public:
    Path();
    Path(QList<Coordinate> pathsC);

    double getDistanceOfCoordinates(Coordinate a, Coordinate b);


private:
    QList<Coordinate> paths;
};

#endif // PATH_H
