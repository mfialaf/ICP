#include "street.h"
#include <QDebug>
#include <math.h>

Street::Street(){}

Street::Street(QString name, Coordinate start, Coordinate end){
    this->start = start;
    this->end = end;
    this->name = name;
    this->line = new QGraphicsLineItem();
    this->line->setLine(start.getX(), start.getY(), end.getX(), end.getY());
    this->line->setPen();
}

Coordinate Street::getStart(){
    return start;
}

Coordinate Street::getEnd(){
    return end;
}

void Street::insertStop(Stop stop){
    stopList.append(stop);
}

void Street::writeList(){
    qDebug() << name << ": ";
    for(int i = 0; i<stopList.size(); i++){
        qDebug() << stopList[i].getName();
    }
}

void Street::sortStops(){
    Stop tmp;
    int x=0;
    if(stopList.size() == 0)
    {
        return;
    }
    else{
        tmp = stopList[0];
    }
    for(int j = 0; j<stopList.size()-x; j++)
    {
        for(int i=1; i<stopList.size()-x; i++){
            if(getDistanceFromStart(tmp.getPosition())>getDistanceFromStart(stopList[i].getPosition())){
                stopList[i-1] = stopList[i];
                stopList[i] = tmp;
            }
            else{
                tmp = stopList[i];
            }
        }
        x++;
    }
}

QString Street::getName(){
    return name;
}

double Street::getDistanceFromStart(Coordinate coordinate){
    return sqrt( pow((start.getX() - coordinate.getX()),2) + pow((start.getY() - coordinate.getY()),2));
}

Stop Street::getStopOnPosition(int position){
    return stopList[position];
}

int Street::getSizeOfStopList(){
    return stopList.size();
}
int Street::getDelay(){
    return delay;
}

void Street::setDelay(int delay)
{
    this->delay = delay;
}
