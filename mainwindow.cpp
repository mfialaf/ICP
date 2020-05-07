#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtWidgets>
#include <QRect>
#include <coordinate.h>
#include <street.h>
#include <path.h>
#include <vehicle.h>
#include <QGraphicsItem>

int a = 90;
int b = 90;
int a2 = 90;
int b2 = 90;
QGraphicsEllipseItem *vehicle;
QGraphicsEllipseItem *vehicle2;
QVector<Vehicle> vehicleVektor;

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
    Coordinate coord(100, 100);
    Coordinate coord2(300, 300);
    Coordinate coord3(100, 300);

    Street street(coord, coord2, "hovno");

    QList<Coordinate> insertData;
    QList<Coordinate> insertData1;
    QList<Coordinate> insertData2;

    insertData.append(coord);
    insertData.append(coord2);
    insertData.append(coord3);
    insertData.append(coord2);

    insertData1.append(coord2);
    insertData1.append(coord);
    insertData1.append(coord2);

    insertData2.append(coord3);
    insertData2.append(coord2);
    insertData2.append(coord);

    Path path(insertData);
    Path path1(insertData1);
    Path path2(insertData2);

    scene->addLine(street.getStart().getX(),street.getStart().getX(),coord2.getX(),coord2.getY());
    scene->addLine(coord2.getX(),coord2.getY(),coord3.getX(),coord3.getY());

    auto text = scene->addText("Ukazka jak to jezdi");
    text->setTextInteractionFlags(Qt::TextEditorInteraction);

    // Co porpojuju, jakej to am signal(F1), ------ , na co to napojuju
    connect(ui->zoomSlider, &QSlider::valueChanged, this ,&MainWindow::zoom);
    //connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this ,SLOT(zoom(int)));  <---- stejny zapis toho sameho

    StartTime();

    //qDebug() << coord.getX() << coord.getY() << street.getStart().getX() << street.getStart().getY();


    vehicleVektor.append(Vehicle(coord, 3, path));
    vehicleVektor.append(Vehicle(coord2, 3, path1));
    vehicleVektor.append(Vehicle(coord3, 3, path2));

    scene->addItem(vehicleVektor[0].getEllipse());

    scene->addItem(vehicleVektor[1].getEllipse());

    scene->addItem(vehicleVektor[2].getEllipse());
    //uprava rasterizace vsech objektu
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    connect(ui->timeSlider, &QSlider::valueChanged, this, &MainWindow::timeChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::StartTime()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this, SLOT(TimeUpdate()));
    timer->start(1000);
}

void MainWindow::TimeUpdate()
{
    //qDebug() << "Update..";
    vehicleVektor[0].vehUpdate();
    vehicleVektor[1].vehUpdate();
    vehicleVektor[2].vehUpdate();


}

void MainWindow::zoom(int val)
{
    auto originalMatice =  ui->graphicsView->transform(); //vrati transformaci matice
    qreal scale = val / 10.0;
    ui->graphicsView->setTransform(QTransform(scale, originalMatice.m12(), originalMatice.m21(), scale, originalMatice.dx(), originalMatice.dy()));
}

void MainWindow::timeChanged(int val)
{
    timer->stop();
    timer->start(1000/val);
}

