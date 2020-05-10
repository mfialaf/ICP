#include "street.h"

/**
 * @brief Street::Street defaultní konstruktor
 */
Street::Street(){}

/**
 * @brief Street::Street konstruktor + nastavení barvy a šířky ulic
 * @param name
 * @param start
 * @param end
 */
Street::Street(QString name, Coordinate start, Coordinate end){
    this->start = start;
    this->end = end;
    this->name = name;
    this->line = new QGraphicsLineItem();
    this->line->setLine(start.getX(), start.getY(), end.getX(), end.getY());
    this->line->setPen(QPen(QColor(Qt::black), 2));
}

/**
 * @brief Street::getStart Vrátí počáteční souřadnice ulice.
 * @return
 */
Coordinate Street::getStart(){
    return start;
}

/**
 * @brief Street::getEnd Vrátí koncové souřadnice ulice.
 * @return
 */
Coordinate Street::getEnd(){
    return end;
}

/**
 * @brief Street::insertStop Vloží zastávku do dané ulice.
 * @param stop vkládaná zastávka
 */
void Street::insertStop(Stop stop){
    stopList.append(stop);
}

/**
 * @brief Street::sortStops Utřídí zastávky v dané ulici od nejbližší po nejvzdálenější (od počátku ulice).
 */
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

/**
 * @brief Street::getName
 * @return Vrátí jméno ulice.
 */
QString Street::getName(){
    return name;
}

/**
 * @brief Street::getDistanceFromStart Zjistí zdálenost zastávky od staru.
 * @param coordinate Souřadnice o které chceme zjistit vzdálenost.
 * @return zjištěná vzdálenost
 */
double Street::getDistanceFromStart(Coordinate coordinate){
    return sqrt( pow((start.getX() - coordinate.getX()),2) + pow((start.getY() - coordinate.getY()),2));
}

/**
 * @brief Street::getStopOnPosition Zjistí zastávku daného pořadí.
 * @param position pořadí
 * @return Pozice zjištěné zastávky.
 */
Stop Street::getStopOnPosition(int position){
    return stopList[position];
}

/**
 * @brief Street::getSizeOfStopList
 * @return Vrátí počet zastávek na ulici.
 */
int Street::getSizeOfStopList(){
    return stopList.size();
}

/**
 * @brief Street::getDelay
 * @return Vrátí zpoždění na ulici.
 */
int Street::getDelay(){
    return delay;
}

/**
 * @brief Street::setDelay Nastaví zpoždění na ulici.
 * @param delay dané zpoždění
 */
void Street::setDelay(int delay)
{
    this->delay = delay;
}

QGraphicsLineItem *Street::getStreetAsQraphicsLine()
{
    return line;
}
