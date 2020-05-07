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

  //  QLabel *label = new QLabel(this); //this rika ze parent je to MainWindow
                                       // o delete se postara MainWindow (ten rodic)
   // label->setText("aohj");

   //1. arametr je nazev objektu do ktereho se mi dany prvek v aktualni iteraci ulozi
   // QVector<int> list{1,2,3,5,8};

   /* for (const auto &item: list) {
        qDebug() << item;
    }
*/

    // Vykresleni sceny
    auto *scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);

//Zelena cara
//    auto line =  scene->addLine(90, 90, 250,200); //vytvori objekt, a vrati zaroven ukazatel na nej
//    line->setPen(QPen(QColor(QString("Green")),1));
//    line->setFlag(QGraphicsItem::ItemIsSelectable); //Jde na ni kliknout

    //Elipsa + text
    streetVector.append(Street(Coordinate(136,89), Coordinate(534,97), "street1"));
    streetVector.append(Street(Coordinate(534,97), Coordinate(140,418), "street2"));
    streetVector.append(Street(Coordinate(140,418), Coordinate(681,499), "street3"));

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

    scene->addLine(streetVector[0].getStart().getX(),streetVector[0].getStart().getY(),streetVector[0].getEnd().getX(),streetVector[0].getEnd().getY());
    scene->addLine(streetVector[1].getStart().getX(),streetVector[1].getStart().getY(),streetVector[1].getEnd().getX(),streetVector[1].getEnd().getY());
    scene->addLine(streetVector[2].getStart().getX(),streetVector[2].getStart().getY(),streetVector[2].getEnd().getX(),streetVector[2].getEnd().getY());

    scene->addEllipse(QRect(stopVector[0].getPosition().getX()-4, stopVector[0].getPosition().getY()-4, 8, 8), QPen(16728320), QBrush(QColor(16728320)));
    scene->addEllipse(QRect(stopVector[1].getPosition().getX()-4, stopVector[1].getPosition().getY()-4, 8, 8), QPen(16728320), QBrush(QColor(16728320)));
    scene->addEllipse(QRect(stopVector[2].getPosition().getX()-4, stopVector[2].getPosition().getY()-4, 8, 8), QPen(16728320), QBrush(QColor(16728320)));
    scene->addEllipse(QRect(stopVector[3].getPosition().getX()-4, stopVector[3].getPosition().getY()-4, 8, 8), QPen(16728320), QBrush(QColor(16728320)));
    scene->addEllipse(QRect(stopVector[4].getPosition().getX()-4, stopVector[4].getPosition().getY()-4, 8, 8), QPen(16728320), QBrush(QColor(16728320)));
    scene->addEllipse(QRect(stopVector[5].getPosition().getX()-4, stopVector[5].getPosition().getY()-4, 8, 8), QPen(16728320), QBrush(QColor(16728320)));

//    auto text = scene->addText("Ukazka jak to jezdi");
//    text->setTextInteractionFlags(Qt::TextEditorInteraction);

    // Co porpojuju, jakej to am signal(F1), ------ , na co to napojuju
    connect(ui->zoomSlider, &QSlider::valueChanged, this ,&MainWindow::zoom);
    //connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this ,SLOT(zoom(int)));  <---- stejny zapis toho sameho

    StartTime();


    //qDebug() << coord.getX() << coord.getY() << street.getStart().getX() << street.getStart().getY();


    vehicleVector.append(Vehicle(Coordinate(136,89), 10, path));
    vehicleVector.append(Vehicle(Coordinate(534,97), 50, path1));
    vehicleVector.append(Vehicle(Coordinate(681,499), 20, path2));

    scene->addItem(vehicleVector[0].getEllipse());

    scene->addItem(vehicleVector[1].getEllipse());

    scene->addItem(vehicleVector[2].getEllipse());
    //uprava rasterizace vsech objektu
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    connect(ui->timeSlider, &QSlider::valueChanged, this, &MainWindow::timeChanged);

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
    if(seconds == 60)
    {
        if(minutes == 60){
            if(hours == 23 && minutes == 60)
            {
                hours = 0;
            }
            hours++;
            minutes = 0;
        }
        minutes++;
        seconds=0;
    }
    seconds++;
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

