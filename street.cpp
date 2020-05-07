#include "street.h"

Street::Street(){}

Street::Street(Coordinate startC, Coordinate endC, QString nameC){
    //this->start = startC;
    start = startC;
    end = endC;
    name = nameC;
}

Coordinate Street::getStart(){
    return start;
}
