#ifndef COORDINATE_H
#define COORDINATE_H

#include <QObject>
#include <QWidget>

struct Coordinates{
    double x;
    double y;
    Coordinates(){
        x=0.0;
        y=0.0;
    }

};

class coordinate : public QWidget
{
    Q_OBJECT
public:
    explicit coordinate(QWidget *parent = nullptr);
    void setX (double x);
    void setY (double y);
    double getX (double x);
    double getY (double y);

private:
    Coordinates coordinates;


signals:

};

#endif // COORDINATE_H
