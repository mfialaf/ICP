#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtWidgets>
#include <QRect>

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
    auto line =  scene->addLine(90, 90, 250,200); //vytvori objekt, a vrati zaroven ukazatel na nej
    line->setPen(QPen(QColor(QString("Green")),1));
    line->setFlag(QGraphicsItem::ItemIsSelectable); //Jde na ni kliknout

    //Elipsa + text
    scene->addEllipse(QRect(90-5,90-5,10,10),QPen(2),QBrush(QColor(11730944)));
    auto text = scene->addText("Ukazka jak to nejezdi");
    text->setTextInteractionFlags(Qt::TextEditorInteraction);

    // Co porpojuju, jakej to am signal(F1), ------ , na co to napojuju
    connect(ui->zoomSlider, &QSlider::valueChanged, this ,&MainWindow::zoom);
    //connect(ui->zoomSlider, SIGNAL(valueChanged(int)), this ,SLOT(zoom(int)));  <---- stejny zapis toho sameho

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::zoom(int val)
{
    auto originalMatice =  ui->graphicsView->transform(); //vrati transformaci matice
    qreal scale = val / 10.0;
    ui->graphicsView->setTransform(QTransform(scale, originalMatice.m12(), originalMatice.m21(), scale, originalMatice.dx(), originalMatice.dy()));
}

