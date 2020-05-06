#ifndef COORDINATE_H
#define COORDINATE_H

//#include <QObject>
//#include <QWidget>
/*
struct Coordinates{
    double x;
    double y;
    Coordinates(){
        x=0.0;
        y=0.0;
    }

};*/

class Coordinate
{
//    Q_OBJECT
public:
    //explicit Coordinate(QWidget *parent = nullptr);

    Coordinate();
    Coordinate(double x, double y);
    void setX (double x);
    void setY (double y);
    double getX ();
    double getY ();
    //Coordinates coordinates;

private:
    //Coordinates coordinates;
    double x;
    double y;


//signals:

};

#endif // COORDINATE_H
