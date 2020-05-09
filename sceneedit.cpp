#include "sceneedit.h"
#include <vehicle.h>

bool rightMousePressed;
int x_ova;
int y_ova;


SceneEdit::SceneEdit(QObject *parent) : QGraphicsScene(parent)
{

}

SceneEdit::SceneEdit(QGraphicsView *view, QVector<Vehicle>* vehicleVector, QVector<Street>* streetVector, Ui::MainWindow* uii, Street* street)
{
    this->view = view;
    this->vehicleVector = vehicleVector;
    this->streetVector = streetVector;
    this->uii = *uii;
    this->street = street;
}

void SceneEdit::printLink(QGraphicsEllipseItem *vehicle)
{
    connect(uii.ButtonDelayPlus, &QPushButton::clicked, this ,&SceneEdit::delayPlus);
    QVector<Vehicle>:: iterator it;
    for (it = vehicleVector->begin(); it != vehicleVector->end(); it++) {
        if(it->visual == vehicle)
        {
            qDebug() << "Linka cislo: " << it->getPath().pathGetLinkName() << " se zastavkami: ";
            QVector<Stop> stopList = it->getPath().pathGetStopList();
            QVector<Stop>:: iterator it2;
            for (it2 = stopList.begin(); it2 != stopList.end(); it2++) {
                qDebug() << it2->getName();
            }
        }
    }
}

//nefunguje
void SceneEdit::getStreet(QGraphicsLineItem* street){
    if(this->street != nullptr){
        if(this->street->getStart().getX() == street->line().x1() && this->street->getEnd().getX() == street->line().x2() && this->street->getStart().getY() == street->line().y1() && this->street->getEnd().getY() == street->line().y2() ) {
            this->street = nullptr;
            return;
        }
    }
    QVector<Street>:: iterator it;
    int i = 0;
    for (it = streetVector->begin(); it != streetVector->end(); it++) {
        if( it->getStart().getX() == street->line().x1() && it->getEnd().getX() == street->line().x2() && it->getStart().getY() == street->line().y1() && it->getEnd().getY() == street->line().y2() ) {
            this->street = streetVector[i].data();
        }
        i++;
    }
}

void SceneEdit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    for(auto* item: items(event->scenePos()) )
    {
        auto vehicle =  dynamic_cast<QGraphicsEllipseItem*>(item);
        if ( vehicle != nullptr)
        {
            //qDebug() << "auto" << vehicleVector[0].data()->visual << "kliknuto na" << vehicle;
            printLink(vehicle);
        }
        if(auto street = dynamic_cast<QGraphicsLineItem*>(item); street != nullptr)
        {
            getStreet(street);
        }
        else
        {
            qDebug() << "jinde";
        }
    }
    // uii.time->setText("hovnohovnohovno");

    QGraphicsScene::mousePressEvent(event);
}
void SceneEdit::delayPlus()
{
    qDebug() << "clicked";
    qDebug() << "clicked2";

}
//void SceneEdit::mousePressEvent2(QMouseEvent *event){
//    if (event->button() == Qt::RightButton)
//    {
//        rightMousePressed = true;
//        _panStartX = event->x();
//        _panStartY = event->y();
//        //setCursor(Qt::ClosedHandCursor);
//        event->accept();
//        return;
//    }
//}

//void SceneEdit::mouseReleaseEvent2(QMouseEvent *event){
//    if (event->button() == Qt::RightButton)
//    {
//        rightMousePressed = false;
//       //    setCursor(Qt::ArrowCursor);
//        event->accept();
//        event->buttons();
//        return;
//    }
//    event->ignore();
//}

//void SceneEdit::mouseMoveEvent2(QMouseEvent *event){
//    if (rightMousePressed)
//    {
//        ui->horizontalScrollBar()->setValue(ui->horizontalScrollBar()->value() - (event->x() - x_ova));
//       // verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - y_ova));
//        _panStartX = event->x();
//        _panStartY = event->y();
//        event->accept();
//        return;
//    }
//    event->ignore();

//}
