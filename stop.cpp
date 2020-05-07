#include "stop.h"

Stop::Stop(){}

Stop::Stop(QString name, Coordinate position)
{
    this->name = name;
    this->position = position;
}

//void Stop::setStreet(Street street){
//    this->street = street;
//}

Coordinate Stop::getPosition(){
    return position;
}

