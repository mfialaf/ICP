#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtWidgets>
#include <QRect>
#include <coordinate.h>
#include <street.h>
#include <path.h>
#include <vehicle.h>
#include <stop.h>
#include <QGraphicsItem>
#include <jsonread.h>

int seconds = 0;
int minutes = 0;
int hours = 0;
int timeupdate = 0;
QVector<Vehicle> vehicleVector;
QVector<Coordinate> coordinateVector;
QVector<Stop> stopVector;
QVector<Street> streetVector;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    //Marin JsonRead
    JsonRead file;
    file.ReadJson(&stopVector,&streetVector);




    // Vykresleni sceny
    auto *scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);

    streetVector.append(Street("street1", Coordinate(136,89), Coordinate(534,97)));
    streetVector.append(Street("street2", Coordinate(534,97), Coordinate(140,418)));
    streetVector.append(Street("street3", Coordinate(140,418), Coordinate(681,499)));

    QList<Coordinate> insertData;
    QList<Coordinate> insertData1;
    QList<Coordinate> insertData2;

    insertData.append(Coordinate(136,89));
    insertData.append(Coordinate(534,97));
    insertData.append(Coordinate(140,418));

    insertData1.append(Coordinate(534,97));
    insertData1.append(Coordinate(136,89));

    insertData2.append(Coordinate(681,499));
    insertData2.append(Coordinate(140,418));
    insertData2.append(Coordinate(534,97));
    insertData2.append(Coordinate(136,89));

    Path path(insertData);
    Path path1(insertData1);
    Path path2(insertData2);

    stopVector.append(Stop("stop1", Coordinate(214.576557, 90.579428)));
    stopVector.append(Stop("stop2", Coordinate(454.799053, 95.408021)));
    stopVector.append(Stop("stop3", Coordinate(450.770913, 164.808469)));
    stopVector.append(Stop("stop4", Coordinate(268.503862, 313.305229)));
    stopVector.append(Stop("stop5", Coordinate(189.434272, 425.401434)));
    stopVector.append(Stop("stop6", Coordinate(443.912037, 463.502542)));

    AddingStopIntoStreet();

//    for(int i = 0; i<streetVector.size(); i++){
//        streetVector[i].writeList();
//    }

    scene->addLine(streetVector[0].getStart().getX(),streetVector[0].getStart().getY(),streetVector[0].getEnd().getX(),streetVector[0].getEnd().getY());
    scene->addLine(streetVector[1].getStart().getX(),streetVector[1].getStart().getY(),streetVector[1].getEnd().getX(),streetVector[1].getEnd().getY());
    scene->addLine(streetVector[2].getStart().getX(),streetVector[2].getStart().getY(),streetVector[2].getEnd().getX(),streetVector[2].getEnd().getY());

    scene->addEllipse(QRect(stopVector[0].getPosition().getX()-4, stopVector[0].getPosition().getY()-4, 8, 8), QPen(16728320), QBrush(QColor(16728320)));
    scene->addEllipse(QRect(stopVector[1].getPosition().getX()-4, stopVector[1].getPosition().getY()-4, 8, 8), QPen(16728320), QBrush(QColor(16728320)));
    scene->addEllipse(QRect(stopVector[2].getPosition().getX()-4, stopVector[2].getPosition().getY()-4, 8, 8), QPen(16728320), QBrush(QColor(16728320)));
    scene->addEllipse(QRect(stopVector[3].getPosition().getX()-4, stopVector[3].getPosition().getY()-4, 8, 8), QPen(16728320), QBrush(QColor(16728320)));
    scene->addEllipse(QRect(stopVector[4].getPosition().getX()-4, stopVector[4].getPosition().getY()-4, 8, 8), QPen(16728320), QBrush(QColor(16728320)));
    scene->addEllipse(QRect(stopVector[5].getPosition().getX()-4, stopVector[5].getPosition().getY()-4, 8, 8), QPen(16728320), QBrush(QColor(16728320)));

    // Co porpojuju, jakej to am signal(F1), ------ , na co to napojuju
    connect(ui->zoomSlider, &QSlider::valueChanged, this ,&MainWindow::zoom);

    StartTime();

    vehicleVector.append(Vehicle(Coordinate(136,89), 60, path));
    vehicleVector.append(Vehicle(Coordinate(534,97), 50, path1));
    vehicleVector.append(Vehicle(Coordinate(681,499), 70, path2));

    scene->addItem(vehicleVector[0].getEllipse());

    scene->addItem(vehicleVector[1].getEllipse());

    scene->addItem(vehicleVector[2].getEllipse());

    //uprava rasterizace vsech objektu
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    connect(ui->timeSlider, &QSlider::valueChanged, this, &MainWindow::timeChanged);

}

void MainWindow::AddingStopIntoStreet(){
    double m;
    double x;
    double y;
    for(int i = 0; i < streetVector.size(); i++){
        for(int j = 0; j<stopVector.size(); j++){
            m = (streetVector[i].getStart().getY() - streetVector[i].getEnd().getY())/(streetVector[i].getStart().getX() - streetVector[i].getEnd().getX());
            x = m*(stopVector[j].getPosition().getX()-streetVector[i].getStart().getX());
            y = stopVector[j].getPosition().getY()-streetVector[i].getStart().getY();
            x = round(x*100)/100;
            y = round(y*100)/100;
            if(x == y)
            {
                streetVector[i].insertStop(stopVector[j]);
            }
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TimeUpdate()
{
    if(timeupdate == 20){
        ui->time->setText(TimeSetter());
        timeupdate = 0;
    }
    else{
        timeupdate++;
    }

    vehicleVector[0].vehUpdate();
    vehicleVector[1].vehUpdate();
    vehicleVector[2].vehUpdate();


}

void MainWindow::timeChanged(int val)
{
    timer->stop();
    timer->start(50/val);
}

void MainWindow::StartTime()
{
    ui->time->setText("<- ZOOM | 00:00:00 | SPEED ->");
    ui->time->setAlignment(Qt::AlignCenter);
    QFont Font("Courier New", 12);
    ui->time->setFont(Font);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(TimeUpdate()));
    timer->start(50);
}

QString MainWindow::TimeSetter(){
    if(seconds == 59)
    {
        if(minutes == 59){
            if(hours == 23 && minutes == 59)
            {
                hours = 0;
                minutes = 0;
                seconds = 0;
            }
            else{
                hours++;
                minutes = 0;
                seconds = 0;
            }
        }
        else{
            minutes++;
            seconds=0;
        }
    }
    else{
        seconds++;
    }
    QString time = "<- ZOOM | ";
    if(hours < 10){
        time.append("0");
        time.append(QString::number(hours));
    }
    else
        time.append(QString::number(hours));
    time.append(":");
    if(minutes < 10){
        time.append("0");
        time.append(QString::number(minutes));
    }
    else
        time.append(QString::number(minutes));
    time.append(":");
    if(seconds < 10){
        time.append("0");
        time.append(QString::number(seconds));
    }
    else
        time.append(QString::number(seconds));
    time.append(" | SPEED ->");
    return time;
}

void MainWindow::zoom(int val)
{
    auto originalMatice =  ui->graphicsView->transform(); //vrati transformaci matice
    qreal scale = val / 10.0;
    ui->graphicsView->setTransform(QTransform(scale, originalMatice.m12(), originalMatice.m21(), scale, originalMatice.dx(), originalMatice.dy()));
}

