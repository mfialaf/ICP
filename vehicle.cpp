#include "vehicle.h"
#include <cstdlib>

Vehicle::Vehicle()
{

}

Vehicle::Vehicle(Coordinate position, double speed, Path path)
{
    if(speed>90)
        speed = 90;

    this->speed = speed;
    this->position = position;
    this->path = path;
    this->visual = new QGraphicsEllipseItem ();
    this->visual->setRect(position.getX()-5, position.getY()-5, 10, 10);
    this->visual->setBrush(QBrush(QColor(rand() % 16770000)));
}

double Vehicle::getDistance(){
    return distance;
}

QGraphicsEllipseItem* Vehicle::getEllipse(){
    return visual;
}

void Vehicle::vehMove(Coordinate coordinate){
    visual->setRect(coordinate.getX()-5, coordinate.getY()-5, 10, 10);
}

void Vehicle::vehUpdate(){
    if(path.stopSameAsPosition(position) && stopWaiter != 20){
        stopWaiter++;
        return;
    }
    else{
        stopWaiter = 0;
    }
    distance+=speed/150;
    if(distance > path.getPathValue())
    {
        distance = 0;
        if(direction)
            direction = false;
        else
            direction = true;
    }
    Coordinate coords = path.getCoordinateByDistance(distance, direction);
    vehMove(coords);
    position = coords;
}

Path Vehicle::getPath()
{
    return path;
}

bool Vehicle::isAtStart()
{
    //   (qRound(position.getX()) == qRound(path.pathGetStart().getX()) && qRound(position.getY()) == qRound(path.pathGetStart().getY()))
    if (compareWithTollerance(position.getX(), path.pathGetStart().getX()) && compareWithTollerance(position.getY(), path.pathGetStart().getY()))
    {
        return true;
    }
    return false;
}

bool Vehicle::compareWithTollerance(double a, double b)
{
    auto diff = a - b;
    return (diff < 3) && (-diff < 3);
}
