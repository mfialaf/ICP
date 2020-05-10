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

Coordinate Path::pathGetStart(){
    return *pathList.begin();
}

double Path::pathGetSpeed(){
    return speed;
}

int Path::getColor()
{
    return color;
}

int Path::pathGetInterval()
{
    return static_cast<int>(interval);
}

QVector<Stop> Path::pathGetStopList()
{
    return stopList;
}

Street* Path::getStreet(double distance,bool direction)
{
    double length = 0;
    if(direction){
        for(int i=0; i<streetList.size(); i++){
            if(length + getDistanceOfCoordinates(streetList[i]->getStart(),streetList[i]->getEnd()) >= distance){
                return streetList[i];
            }
            length += getDistanceOfCoordinates(streetList[i]->getStart(),streetList[i]->getEnd());
        }
        return streetList[streetList.size()-1];
    }
    else{
        for(int i=streetList.size()-1; i>=0; i--){
            if(length + getDistanceOfCoordinates(streetList[i]->getStart(),streetList[i]->getEnd()) >= distance){
                return streetList[i];
            }
            length += getDistanceOfCoordinates(streetList[i]->getStart(),streetList[i]->getEnd());
        }
        return streetList[0];
    }

}

int Path::pathGetLinkName()
{
    return pathNumber;
}

Path::Path(QVector<QString> streetNames, double speed, double pathNumber, double interval, int color){
    this->streetNames = streetNames;
    this->speed = speed;
    this->pathNumber = pathNumber;
    this->interval = interval;
    this->color = color;
}

double Path::getDistanceOfCoordinates(Coordinate a, Coordinate b)
{
    return sqrt( pow((a.getX() - b.getX()),2) + pow((a.getY() - b.getY()),2));
}

bool Path::stopSameAsPosition(Coordinate coordinate){
    for(int i = 0; i<stopList.size(); i++){
        if(qRound(coordinate.getX()) == qRound(stopList[i].getPosition().getX()) && qRound(coordinate.getY()) == qRound(stopList[i].getPosition().getY())){
            return true;

        }
    }
    return false;
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

void Path::setStreetsAndStops(QVector<Street*> streetVector){
    int justFirstStartAddedFlag = 1;
    for(int i = 0; i<streetNames.size(); i++){
        for(int j = 0; j<streetVector.size(); j++){
            if(!QString::compare(streetVector[j]->getName(), streetNames[i])){
                if(justFirstStartAddedFlag){
                    pathList.append(streetVector[j]->getStart());
                    justFirstStartAddedFlag=0;
                }
                for(int k = 0; k<streetVector[j]->getSizeOfStopList(); k++){
                    pathList.append(streetVector[j]->getStopOnPosition(k).getPosition());
                    stopNames.append(streetVector[j]->getStopOnPosition(k).getName());
                    stopList.append(streetVector[j]->getStopOnPosition(k));

                }
                pathList.append(streetVector[j]->getEnd());
                streetList.append(streetVector[j]);
            }
        }
    }
}

