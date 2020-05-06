#include "nejakywidget.h"
#include <QPainter>

nejakyWidget::nejakyWidget(QObject *parent) : QObject(parent)
{

}

void nejakyWidget::paintEvent(QPaintEvent *event)
{
   // QPainter p();
    QPainter p;
    p.drawEllipse(50,50,100,20);


}
