#include "street.h"

Street::Street(){}

Street::Street(Coordinate start, Coordinate end, QString name){
    this->start = start;
    this->end = end;
    this->name = name;
}

Coordinate Street::getStart(){
    return start;
}

Coordinate Street::getEnd(){
    return end;
}

void Street::insertStop(Stop stop){
    stopList.append(stop.getPosition());
}


//pri pridavani zastavek do path, vypocitam vzdalenost zastavky od startu a podle toho vim kterou zastavku mam pridat jako prvni (pouze pri vice zastavek)
