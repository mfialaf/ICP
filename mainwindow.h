#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMap>
#include <QDebug>
#include <QtWidgets>
#include <QRect>
#include <coordinate.h>
#include <QGraphicsItem>
#include <jsonread.h>
#include <sceneedit.h>
#include <QDateTime>
#include <street.h>
#include <QGraphicsScene>
#include <street.h>
#include <path.h>
#include <vehicle.h>
#include <stop.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    // POkud chci mit objekt co vysila signaly musi to dedit z QObject

public:
    QVector<Vehicle> vehicleVector;
    QVector<Coordinate> coordinateVector;
    QVector<Stop> stopVector;
    QVector<Street*> streetVector;
    QVector<Path> pathVector;
    QGraphicsScene* scene;

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void StartTime();
    QString TimeSetter();
    void AddingStopIntoStreet();
    void setPaths();
    void setScene(QVector<Street*> streetVector);
    void startVehicle();
    void resetDelay();
    void increaseDelay();
    void decreaseDelay();
    void increaseHour();
    void decreaseHour();
    void increaseMinute();
    void decreaseMinute();
    void increaseSecond();
    void decreaseSecond();
    void setNewTime();

signals:
    void signalChanged(int val);

public slots:
    void TimeUpdate();

private slots:
    void zoom(int val); // kdyz zde mam ukazatel tak alt + Enter mi vyvori deklaraci te funkce
    void timeChanged (int val);
private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int seconds = 0;
    int minutes = 0;
    int hours = 0;
    int timeupdate = 0;
    int DelaydedStreet = -1;
};
#endif // MAINWINDOW_H
