#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtWidgets>
#include <QRect>
#include <coordinate.h>
#include <QGraphicsItem>
#include <jsonread.h>
#include <sceneedit.h>

int seconds = 59;
int minutes = 29;
int hours = 0;
int timeupdate = 0;
QVector<Vehicle> vehicleVector;
QVector<Coordinate> coordinateVector;
QVector<Stop> stopVector;
QVector<Street> streetVector;
QVector<Path> pathVector;
QGraphicsScene* scene;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    //Marin JsonRead
    JsonRead file;
    file.ReadJson(&stopVector,&streetVector,&pathVector);



    // Vykresleni sceny
    scene = new SceneEdit(ui->graphicsView);
    ui->graphicsView->setScene(scene);

    AddingStopIntoStreet();
    setPaths();
    setScene(streetVector);

    // Co porpojuju, jakej to am signal(F1), ------ , na co to napojuju
    connect(ui->zoomSlider, &QSlider::valueChanged, this ,&MainWindow::zoom);

    StartTime();
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
        streetVector[i].sortStops();
    }
}

void MainWindow::setPaths(){
    for(int i=0; i<pathVector.size(); i++){
        pathVector[i].setStreetsAndStops(streetVector);
    }
}

void MainWindow::setScene(QVector<Street> streetVector) //klomen
{
    for(int i = 0; i < streetVector.size();i++)
    {
        scene->addLine(streetVector[i].getStart().getX(),streetVector[i].getStart().getY(),streetVector[i].getEnd().getX(),streetVector[i].getEnd().getY());
        for(int j = 0; j < streetVector[i].getSizeOfStopList() ;j++)
        {
            scene->addEllipse(QRect(streetVector[i].getStopOnPosition(j).getPosition().getX()-4, streetVector[i].getStopOnPosition(j).getPosition().getY()-4, 8, 8), QPen(16728320), QBrush(QColor(16728320)));
        }
    }
}

void MainWindow::startVehicle()
{
    QVector<Path>::iterator it1;
    for (it1 = pathVector.begin(); it1 != pathVector.end(); it1++)
    {
        if(hours > 6 && hours < 23){
            if (((hours * 60 + minutes) % it1->pathGetInterval() == 0) && seconds == 0)
            {
                vehicleVector.append(Vehicle((*it1).pathGetStart(), (*it1).pathGetSpeed(), (*it1), (*it1).getColor()));
                scene->addItem(vehicleVector[vehicleVector.size()-1].getEllipse());
                //qDebug() << "start linka:" << it1->pathGetLinkName();
            }
        }
        else{
        if (((hours * 60 + minutes) % 30 == 0) && seconds == 0)
        {
            vehicleVector.append(Vehicle((*it1).pathGetStart(), (*it1).pathGetSpeed(), (*it1), (*it1).getColor()));
            scene->addItem(vehicleVector[vehicleVector.size()-1].getEllipse());
            //qDebug() << "start linka:" << it1->pathGetLinkName();
        }
        }
    }

    QVector<Vehicle>:: iterator it;
    for (it = vehicleVector.begin(); it != vehicleVector.end(); it++)
    {
        if(it->isAtStart() && it->getDistance() > 100)
        {
            //qDebug() << "konec linka:" << it->getPath().pathGetLinkName() << it->getDistance() << vehicleVector.size();
            scene->removeItem((*it).getEllipse());
            vehicleVector.erase(it);
            if(vehicleVector.size()==0){
                return;
            }
            it--;
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
        startVehicle();
    }
    else{
        timeupdate++;
    }
    QVector<Vehicle>:: iterator it;
    for (it = vehicleVector.begin(); it != vehicleVector.end(); it++) {
        it->vehUpdate();
    }
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

