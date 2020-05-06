#ifndef VEHICLE_H
#define VEHICLE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class vehicle : public QWidget
{
    Q_OBJECT
public:
    explicit vehicle(QWidget *parent = nullptr);

signals:

};

#endif // VEHICLE_H
