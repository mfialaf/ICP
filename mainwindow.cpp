#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QLabel *label = new QLabel(this); //this rika ze parent je to MainWindow
                                       // o delete se postara MainWindow (ten rodic)
    label->setText("aohj");

        //1. arametr je nazev objektu do ktereho se mi dany prvek v aktualni iteraci ulozi
        //
    QVector<int> list{1,2,3,5,8};

    for (const auto &item: list) {
        qDebug() << item;
    }

                                    // Vycetl jsem z bazove tridy, je potreba napsat typ
    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), this, SLOT(onValueChanged(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onValueChanged(int val)
{
    qDebug() << "value" << val ;
}

