#ifndef STREET_H
#define STREET_H

#include <QObject>
#include <QWidget>
#include <coordinate.h>

class Street : public QWidget
{
//    Q_OBJECT
public:
//    explicit Street(QWidget *parent = nullptr);

    Street();
    Street(Coordinate startC, Coordinate endC, QString nameC);
    Coordinate getStart();

private:
    Coordinate start;
    Coordinate end;
    QString name;


signals:

};

#endif // STREET_H
