#ifndef COORDINATE_H
#define COORDINATE_H

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
