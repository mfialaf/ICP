#include "street.h"
/*
Street::Street(QWidget *parent) : QWidget(parent)
{

}
*/

Street::Street(Coordinate startC, Coordinate endC, QString nameC){
    //this->start = startC;
    start = startC;
    end = endC;
    name = nameC;
}
