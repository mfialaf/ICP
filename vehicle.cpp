/** @brief Imitace dopravních spojů.

    Semestrální projekt - aplikace pro zobrazení linek hromadné dopravy a sledování jejich pohybu.
    @authors Daniel Kamenický xkamen21 & Marek Fiala xfiala60
    @date Květen 2020
    @sub ICP Seminář C++
*/

#include "vehicle.h"
#include <cstdlib>

//Vehicle v konecne zastavce bude cekat dobu, ktera odpovida intervalu. Do vehicle pridat timer ktery bude zvysovat velikost pri tiku hodin, pri naplneni anulovat a vyslat zpet.

Vehicle::Vehicle()
{

}

Vehicle::Vehicle(Coordinate position, double speed, Path path, int color)
{
    if(speed>90)
        speed = 90;
    if(speed<50)
        speed = 50;

    this->speed = speed;
    this->position = position;
    this->path = path;
    this->visual = new QGraphicsEllipseItem ();
    this->visual->setRect(position.getX()-5, position.getY()-5, 10, 10);
    this->visual->setBrush(QBrush(QColor(color)));
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

void Vehicle::vehUpdate(int hours){
    int WaitingTime = 0;
    if(path.stopSameAsPosition(position) && stopWaiter != 300 && countWait == 0){
        stopWaiter++;
        return;
    }
    else{
        countWait++;
        stopWaiter = 0;
    }
    if(!path.stopSameAsPosition(position) && countWait != 0){
        countWait = 0;
    }
    Street* street = path.getStreetWithVehicle(distance, direction);
    distance+=speed/(200+street->getDelay());
    if(distance >= path.getPathValue())
    {
        if(hours==23 || hours<6){
            WaitingTime = 30*60*20;
        }
        else{
            WaitingTime = path.pathGetInterval()*60*20;
        }
        if((EndPathWaiter < WaitingTime) && direction){
            EndPathWaiter++;
            return;
        }
        else{
            distance = 0;
            EndPathWaiter = 0;
            if(direction)
                direction = false;
            else
                direction = true;
        }
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
    return (diff < 10) && (-diff < 10);
}
