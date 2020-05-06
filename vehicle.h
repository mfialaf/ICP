#include <coordinate.h>
#include <path.h>
#include <QtWidgets>
#include <QGraphicsScene>

#ifndef VEHICLE_H
#define VEHICLE_H


class Vehicle : public QGraphicsScene
{

    Q_OBJECT
public:
    explicit Vehicle(QObject *parent = nullptr);

    Vehicle(Coordinate position, double speed, Path path);

private:
    Coordinate position;
    double speed;
    double distance = 0;
    Path path;
    QGraphicsEllipseItem *mark;

signals:

};



#endif // VEHICLE_H
