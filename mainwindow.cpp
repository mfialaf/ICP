#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtWidgets>
#include <QRect>
#include <coordinate.h>
#include <QGraphicsItem>
#include <jsonread.h>
#include <sceneedit.h>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Marin JsonRead
    JsonRead file;
    file.ReadJson(&stopVector,&streetVector,&pathVector);

    // Vykresleni sceny
    scene = new SceneEdit(ui->graphicsView, &vehicleVector, streetVector,ui, &DelaydedStreet);
    scene->setBackgroundBrush(Qt::lightGray);
    ui->graphicsView->setScene(scene);


    AddingStopIntoStreet();
    setPaths();
    setScene(streetVector);

    // Co porpojuju, jakej to am signal(F1), ------ , na co to napojuju
    connect(ui->zoomSlider, &QSlider::valueChanged, this ,&MainWindow::zoom);
    connect(ui->ButtonDelayPlus, &QPushButton::pressed, this, &MainWindow::increaseDelay);
    connect(ui->ButtonDelayMinus, &QPushButton::pressed, this, &MainWindow::decreaseDelay);
    connect(ui->ButtonDelayReset, &QPushButton::pressed, this, &MainWindow::resetDelay);

    connect(ui->ButtonHourUp, &QPushButton::pressed, this, &MainWindow::increaseHour);
    connect(ui->ButtonHourDown, &QPushButton::pressed, this, &MainWindow::decreaseHour);
    connect(ui->ButtonMinuteUp, &QPushButton::pressed, this, &MainWindow::increaseMinute);
    connect(ui->ButtonMinuteDown, &QPushButton::pressed, this, &MainWindow::decreaseMinute);
    connect(ui->ButtonSecondUp, &QPushButton::pressed, this, &MainWindow::increaseSecond);
    connect(ui->ButtonSecondDown, &QPushButton::pressed, this, &MainWindow::decreaseSecond);
    connect(ui->setTime, &QPushButton::pressed, this, &MainWindow::setNewTime);

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
            m = (streetVector[i]->getStart().getY() - streetVector[i]->getEnd().getY())/(streetVector[i]->getStart().getX() - streetVector[i]->getEnd().getX());
            x = m*(stopVector[j].getPosition().getX()-streetVector[i]->getStart().getX());
            y = stopVector[j].getPosition().getY()-streetVector[i]->getStart().getY();
            x = round(x*100)/100;
            y = round(y*100)/100;
            if(x == y)
            {
                streetVector[i]->insertStop(stopVector[j]);
            }
        }
        streetVector[i]->sortStops();
    }
}

void MainWindow::resetDelay(){
    if(DelaydedStreet == -1){
        return;
    }
    else{
        streetVector[DelaydedStreet]->setDelay(0);
        int delay = streetVector[DelaydedStreet]->getDelay();
        delay = delay/200;
        if(delay>100){
            delay = 100;
        }
        ui->printDelay->setText("Delay is on: "+QString::number(delay)+"%");
    }
}

void MainWindow::increaseDelay(){

    if(DelaydedStreet == -1){
        return;
    }
    else{
        streetVector[DelaydedStreet]->setDelay(streetVector[DelaydedStreet]->getDelay()+200);
        int delay = streetVector[DelaydedStreet]->getDelay();
        delay = delay/200;
        if(delay>100){
            delay = 100;
        }
        ui->printDelay->setText("Delay is on: "+QString::number(delay)+"%");
    }
}

void MainWindow::decreaseDelay(){
    if(DelaydedStreet == -1){
        return;
    }
    else if(streetVector[DelaydedStreet]->getDelay()==0){
        return;
    }
    else{
        if(streetVector[DelaydedStreet]->getDelay() > 20000){
            streetVector[DelaydedStreet]->setDelay(20000);
        }
        streetVector[DelaydedStreet]->setDelay(streetVector[DelaydedStreet]->getDelay()-200);
        int delay = streetVector[DelaydedStreet]->getDelay();
        delay = delay/200;
        if(delay>100){
            delay = 100;
        }
        ui->printDelay->setText("Delay is on: "+QString::number(delay)+"%");
    }
}

void MainWindow::increaseHour()
{
    int tmp = static_cast<int>(ui->hour->text().toDouble());
    tmp ++;
    if(tmp > 23){
        tmp = 0;
    }
    if(tmp < 10){
        ui->hour->setText("0"+QString::number(tmp));
    }
    else{
        ui->hour->setText(QString::number(tmp));
    }
}

void MainWindow::decreaseHour()
{
    int tmp = static_cast<int>(ui->hour->text().toDouble());
    tmp --;
    if(tmp < 0){
        tmp = 23;
    }
    if(tmp < 10){
        ui->hour->setText("0"+QString::number(tmp));
    }
    else{
        ui->hour->setText(QString::number(tmp));
    }
}

void MainWindow::increaseMinute()
{
    int tmp = static_cast<int>(ui->minute->text().toDouble());
    tmp ++;
    if(tmp > 59){
        tmp = 0;
    }
    if(tmp < 10){
        ui->minute->setText("0"+QString::number(tmp));
    }
    else{
        ui->minute->setText(QString::number(tmp));
    }
}

void MainWindow::decreaseMinute()
{
    int tmp = static_cast<int>(ui->minute->text().toDouble());
    tmp --;
    if(tmp < 0){
        tmp = 59;
    }
    if(tmp < 10){
        ui->minute->setText("0"+QString::number(tmp));
    }
    else{
        ui->minute->setText(QString::number(tmp));
    }
}

void MainWindow::increaseSecond()
{
    int tmp = static_cast<int>(ui->second->text().toDouble());
    tmp ++;
    if(tmp > 59){
        tmp = 0;
    }
    if(tmp < 10){
        ui->second->setText("0"+QString::number(tmp));
    }
    else{
        ui->second->setText(QString::number(tmp));
    }
}


void MainWindow::decreaseSecond()
{
    int tmp = static_cast<int>(ui->second->text().toDouble());
    tmp --;
    if(tmp < 0){
        tmp = 59;
    }
    if(tmp < 10){
        ui->second->setText("0"+QString::number(tmp));
    }
    else{
        ui->second->setText(QString::number(tmp));
    }
}

void MainWindow::setNewTime()
{
    this->seconds = (static_cast<int>(ui->second->text().toDouble())-1);
    this->minutes = static_cast<int>(ui->minute->text().toDouble());
    this->hours = static_cast<int>(ui->hour->text().toDouble());
    ui->time->setText(TimeSetter());
    QVector<Vehicle>:: iterator it;
    for (it = vehicleVector.begin(); it != vehicleVector.end(); it++)
    {
        scene->removeItem((*it).getEllipse());
        vehicleVector.erase(it);
        if(vehicleVector.size()==0){
            return;
        }
        it--;
    }
}

void MainWindow::setPaths(){
    for(int i=0; i<pathVector.size(); i++){
        pathVector[i].setStreetsAndStops(streetVector);
    }
}

void MainWindow::setScene(QVector<Street*> streetVector) //klomen
{
    for(int i = 0; i < streetVector.size();i++)
    {
        scene->addItem(streetVector[i]->getStreetAsQraphicsLine());
        for(int j = 0; j < streetVector[i]->getSizeOfStopList() ;j++)
        {
            scene->addEllipse(QRect(streetVector[i]->getStopOnPosition(j).getPosition().getX()-4, streetVector[i]->getStopOnPosition(j).getPosition().getY()-4, 8, 8), QPen(16728320), QBrush(QColor(16728320)));
        }
    }
}

void MainWindow::startVehicle()
{
    QVector<Path>::iterator it1;
    for (it1 = pathVector.begin(); it1 != pathVector.end(); it1++)
    {
        if(hours > 5 && hours < 23){
            if ((((hours-6) * 60 + minutes) % it1->pathGetInterval() == 0) && seconds == 0)
            {
                vehicleVector.append(Vehicle((*it1).pathGetStart(), (*it1).pathGetSpeed(), (*it1), (*it1).getColor()));
                scene->addItem(vehicleVector[vehicleVector.size()-1].getEllipse());
            }
        }
        else{
        if (((hours * 60 + minutes) % 30 == 0) && seconds == 0)
        {
            vehicleVector.append(Vehicle((*it1).pathGetStart(), (*it1).pathGetSpeed(), (*it1), (*it1).getColor()));
            scene->addItem(vehicleVector[vehicleVector.size()-1].getEllipse());
        }
        }
    }

    QVector<Vehicle>:: iterator it;
    for (it = vehicleVector.begin(); it != vehicleVector.end(); it++)
    {
        if(it->isAtStart() && it->getDistance() > 100)
        {
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
    QDateTime UTC(QDateTime::currentDateTimeUtc());
    QDateTime local(UTC.toLocalTime());
    hours = local.time().hour();
    minutes = local.time().minute();
    seconds = local.time().second();
    if(hours < 10){
        ui->hour->setText("0"+QString::number(hours));
    }
    else{
        ui->hour->setText(QString::number(hours));
    }
    if(minutes < 10){
        ui->minute->setText("0"+QString::number(minutes));
    }
    else{
        ui->minute->setText(QString::number(minutes));
    }
    if(seconds < 10){
        ui->second->setText("0"+QString::number(seconds));
    }
    else{
        ui->second->setText(QString::number(seconds));
    }
    ui->time->setText(TimeSetter());
    ui->time->setAlignment(Qt::AlignCenter);
    ui->hour->setAlignment(Qt::AlignCenter);
    ui->minute->setAlignment(Qt::AlignCenter);
    ui->second->setAlignment(Qt::AlignCenter);
    QFont Font("Courier New", 12);
    ui->time->setFont(Font);
    ui->hour->setFont(Font);
    ui->minute->setFont(Font);
    ui->second->setFont(Font);
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

