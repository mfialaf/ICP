#include "hokuspokus.h"
#include <QPainter>
#include <QDebug>
#include <QtWidgets>

hokusPokus::hokusPokus(QWidget *parent) : QWidget(parent)
{

}

void hokusPokus::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawEllipse(rect());

}

void hokusPokus::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->pos();
    event->accept(); // tim reknu ze uz jsem to zpravoal
    QWidget::mousePressEvent(event); //provolam to prededene nazpet

}
