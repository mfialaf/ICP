#include "street.h"
#include <QDebug>

Street::Street(){}

Street::Street(QString name, Coordinate start, Coordinate end){
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
    stopList.append(stop);
}

void Street::writeList(){
    qDebug() << name << ": ";
    for(int i = 0; i<stopList.size(); i++){
        qDebug() << stopList[i].getName() << stopList[i].getName();
    }
}
//pri pridavani zastavek do path, vypocitam vzdalenost zastavky od startu a podle toho vim kterou zastavku mam pridat jako prvni (pouze pri vice zastavek)
