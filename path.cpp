#include "path.h"
#include <math.h>
#include <QDebug>

//MARIN Neni KOKOT <3, ale kamen je kokot

Path::Path()
{

}

Path::Path(QList<Coordinate> pathList)
{
    this->pathList = pathList;
}

double Path::getDistanceOfCoordinates(Coordinate a, Coordinate b)
{
    return sqrt( pow((a.getX() - b.getX()),2) + pow((a.getY() - b.getY()),2));
}

Coordinate Path::getCoordinateByDistance(double distance, bool direction)
{
    bool flag = true;
    double length = 0;

    Coordinate a;
    Coordinate b;

    if(direction){
        QList<Coordinate>::iterator iterator = pathList.begin();
        for(int i = 0; i < pathList.size()-1; ++i)
        {
            flag = false;
            a = *iterator;
            b = *(++iterator);

            if(length + getDistanceOfCoordinates(a,b) >= distance){
                break;
            }

            length += getDistanceOfCoordinates(a,b);
        }
    }
    else
    {
        QList<Coordinate>::iterator iterator = pathList.end();
        iterator--;
        for(int i = 0; i < pathList.size()-1; ++i)
        {
            flag = false;
            a = *iterator;
            b = *(--iterator);

            if(length + getDistanceOfCoordinates(a,b) >= distance){
                break;
            }

            length += getDistanceOfCoordinates(a,b);
        }
    }


    // Vyresit konec cesty
    if(flag)
    {
        Coordinate nemacestu;
        return nemacestu;
    }

    double driven = (distance - length) / getDistanceOfCoordinates(a, b);

    return Coordinate(a.getX() + (b.getX() - a.getX()) * driven, a.getY() + (b.getY() - a.getY()) * driven);
}

double Path::getPathValue()
{
    Coordinate a,b;
    double size = 0;

    QList<Coordinate>::iterator iterator = pathList.begin();
    for(int i = 0; i < pathList.size()-1; ++i)
    {
        a = *iterator;
        b = *(++iterator);
        size += getDistanceOfCoordinates(a, b);
    }
    return size;
}



