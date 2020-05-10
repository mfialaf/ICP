#ifndef PATH_H
#define PATH_H

#include <QList>
#include <coordinate.h>
#include <stop.h>
#include <street.h>

class Path
{
public:
    Path();
    Path(QList<Coordinate> pathList);
    Path(QVector<QString> streetNames, double speed, double linkNumber, double interval, int color);

    double getDistanceOfCoordinates(Coordinate a, Coordinate b);
    Coordinate getCoordinateByDistance (double distance, bool direction);
    double getPathValue();
    bool stopSameAsPosition(Coordinate coordinate);
    void setStreetsAndStops(QVector<Street*> streetVector);
    Coordinate pathGetStart();
    double pathGetSpeed();
    int getColor();
    int pathGetInterval();
    int pathGetLinkName();
    QVector<Stop> pathGetStopList();
    Street* getStreet(double distance, bool direction);


private:
    QList<Coordinate> pathList;
    QVector<Stop> stopList;
    QVector<Street*> streetList;
    QVector<QString> streetNames;
    QVector<QString> stopNames;
    double speed;
    double pathNumber; //Jmeno linky
    double interval;
    int color;
};

#endif // PATH_H
