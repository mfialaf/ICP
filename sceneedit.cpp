#include "sceneedit.h"
#include <vehicle.h>
#include<QPen>

bool rightMousePressed;
int x_ova;
int y_ova;


SceneEdit::SceneEdit(QObject *parent) : QGraphicsScene(parent)
{
}

SceneEdit::SceneEdit(QGraphicsView *view, QVector<Vehicle>* vehicleVector, QVector<Street*> streetVector, Ui::MainWindow* uii, int* PositionOfDelaydedstreet)
{
    this->view = view;
    this->vehicleVector = vehicleVector;
    this->streetVector = streetVector;
    this->uii = *uii;
    this->PositionOfDelaydedstreet = PositionOfDelaydedstreet;
    setLinkNo();
}

QString SceneEdit::printLink(QGraphicsEllipseItem *vehicle)
{
    bool flag = true;
    QString output = "Link ";
    QVector<Vehicle>:: iterator it;
    for (it = vehicleVector->begin(); it != vehicleVector->end(); it++) {
        if(it->getEllipse() == vehicle)
        {
            flag = false;
            output.append(QString::number(it->getPath().pathGetLinkName(),10));
            output.append('\n');

            //qDebug() << it->getPath().pathGetLinkName() << " se zastavkami: ";
            QVector<Stop> stopList = it->getPath().pathGetStopList();
            QVector<Stop>:: iterator it2;
            for (it2 = stopList.begin(); it2 != stopList.end(); it2++) {
                output.append(" ->  ");
                output.append(it2->getName());
                output.append('\n');
               // qDebug().noquote() << output;
            }
           // qDebug() << it->getPath().
        }
    }
    if(flag)
    {
        output = "Link -";
    }
    return output;
}

void SceneEdit::getStreet(QGraphicsLineItem* street){
    for(int i = 0; i<streetVector.size(); i++){
        if( streetVector[i]->getStart().getX() == street->line().x1() && streetVector[i]->getEnd().getX() == street->line().x2() && streetVector[i]->getStart().getY() == street->line().y1() && streetVector[i]->getEnd().getY() == street->line().y2() ) {
            if(*PositionOfDelaydedstreet == i){
                streetVector[i]->line->setPen(QPen(QColor(Qt::black),2));
                *PositionOfDelaydedstreet = -1;
            }
            else{
                if(*PositionOfDelaydedstreet != -1)
                {
                    streetVector[*PositionOfDelaydedstreet]->line->setPen(QPen(QColor(Qt::black),2));
                }
                streetVector[i]->line->setPen(QPen(QColor(Qt::red),2));
                *PositionOfDelaydedstreet = i;
            }
            return;
        }
    }
}

void SceneEdit::resetMarkedLine()
{
    if(*PositionOfDelaydedstreet != -1)
    {
        streetVector[*PositionOfDelaydedstreet]->line->setPen(QPen(QColor(Qt::black),2));
        *PositionOfDelaydedstreet = -1;
    }
}

void SceneEdit::setLinkNo()
{
    this->uii.VehicleData->setFontWeight(3);
    this->uii.VehicleData->setText("Link -");
    this->uii.VehicleData->setAlignment(Qt::AlignCenter);
}

void SceneEdit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    for(auto* item: items(event->scenePos()) )
    {
        auto vehicle =  dynamic_cast<QGraphicsEllipseItem*>(item);
        if ( vehicle != nullptr)
        {
            resetMarkedLine();
            //qDebug() << "auto" << vehicleVector[0].data()->visual << "kliknuto na" << vehicle;
            uii.VehicleData->setText(printLink(vehicle));
            uii.VehicleData->setAlignment(Qt::AlignCenter);
            return;
        }
        else if(auto street = dynamic_cast<QGraphicsLineItem*>(item); street != nullptr)
        {
            getStreet(street);
            setLinkNo();
            return;
        }
        else
        {
            resetMarkedLine();
            qDebug() << "jinde";
        }
    }
    resetMarkedLine();
    setLinkNo();

    QGraphicsScene::mousePressEvent(event);
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
