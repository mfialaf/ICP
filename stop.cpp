/** @brief Imitace dopravních spojů.

    Semestrální projekt - aplikace pro zobrazení linek hromadné dopravy a sledování jejich pohybu.
    @authors Daniel Kamenický xkamen21 & Marek Fiala xfiala60
    @date Květen 2020
    @sub ICP Seminář C++
*/

#include "stop.h"
/**
 * @brief Stop::Stop defaultní konstruktor
 */
Stop::Stop(){}

/**
 * @brief Stop::Stop konstruktor
 * @param name
 * @param position
 */
Stop::Stop(QString name, Coordinate position)
{
    this->name = name;
    this->position = position;
}

/**
 * @brief Stop::getPosition
 * @return Vrátí pozici zastávky.
 */
Coordinate Stop::getPosition(){
    return position;
}

/**
 * @brief Stop::getName
 * @return Vrátí jméno zastávky.
 */
QString Stop::getName(){
    return name;
}

