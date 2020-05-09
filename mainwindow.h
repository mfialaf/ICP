#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMap>
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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void StartTime();
    QString TimeSetter();
    void AddingStopIntoStreet();
    void setPaths();
    void setScene(QVector<Street> streetVector, QGraphicsScene* scene);
    void startVehicle(QVector<Path> pathVector);

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
};
#endif // MAINWINDOW_H
