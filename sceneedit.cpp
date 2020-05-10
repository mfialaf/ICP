#include "sceneedit.h"
#include <vehicle.h>
#include<QPen>

bool rightMousePressed;
int x_ova;
int y_ova;

/**
 * @brief SceneEdit::SceneEdit defaultni konstruktor
 * @param parent rodic typu QParent
 */
SceneEdit::SceneEdit(QObject *parent) : QGraphicsScene(parent)
{
}

/**
 * @brief SceneEdit::SceneEdit konstriktor
 * @param view
 * @param vehicleVector
 * @param streetVector
 * @param uii
 * @param PositionOfDelaydedstreet
 */
SceneEdit::SceneEdit(QGraphicsView *view, QVector<Vehicle>* vehicleVector, QVector<Street*> streetVector, Ui::MainWindow* uii, int* PositionOfDelaydedstreet)
{
    this->view = view;
    this->vehicleVector = vehicleVector;
    this->streetVector = streetVector;
    this->uii = *uii;
    this->PositionOfDelaydedstreet = PositionOfDelaydedstreet;
    setLinkInfo();
}

/**
 * @brief SceneEdit::printLink
 * @param vehicle
 * @return vraci
 */
QString SceneEdit::printLink(QGraphicsEllipseItem *vehicle)
{
    bool flag = true;
    QString output = "Link ";
    QString timetable = "Starting station timetable:\n";
    QVector<Vehicle>:: iterator it;
    for (it = vehicleVector->begin(); it != vehicleVector->end(); it++) {
        if(it->getEllipse() == vehicle)
        {
            flag = false;
            output.append(QString::number(it->getPath().pathGetLinkName(),10));
            output.append("\n\nStops: \n");

            //qDebug() << it->getPath().pathGetLinkName() << " se zastavkami: ";
            QVector<Stop> stopList = it->getPath().pathGetStopList();
            QVector<Stop>:: iterator it2;
            for (it2 = stopList.begin(); it2 != stopList.end(); it2++) {
                output.append(" ->  ");
                output.append(it2->getName());
                output.append('\n');
            }

            //output.append("\n\n\nStarting station timetable:\n");
            for(int i = 0; i < 6; i++)
            {
                timetable.append(QString::number(i));
                timetable.append(": 00 30 \n");
            }
            for(int i = 6; i< 23; i++)
            {
                timetable.append(QString::number(i));
                timetable.append(": ");
                if(it->getPath().pathGetInterval() == 1)
                {
                    timetable.append("every minute");
                }
                else if(it->getPath().pathGetInterval() == 2 || it->getPath().pathGetInterval() == 3)
                {
                    timetable.append("every ");
                    timetable.append(QString::number(it->getPath().pathGetInterval()));
                    timetable.append(" minutes");
                }
                else
                {
                    for(int j = 0; j < 59; j++)
                    {
                        //output.append(QString::number((i*60+j) % (it->getPath().pathGetInterval)()));
                        if((((i-6)*60+j) % (it->getPath().pathGetInterval)()) == 0)
                        {
                            if(j<10)
                            {
                                timetable.append("0");
                            }
                                timetable.append(QString::number(j));
                                timetable.append(" ");
                        }
                    }
                }
                timetable.append("\n");
            }
            timetable.append("23: 00 30 \n");
            uii.TimeTable->setText(timetable);

            //qDebug() << it->getPath().getStreetList().size();
            QVector<Street*> tmpList =  it->getPath().getStreetList();
            for(int i = 0; i < tmpList.size(); i++)
            {
                tmpList[i]->line->setPen(QPen(QColor(Qt::green),2));
            }

        }
    }
    if(flag)
    {
        output = "Link -";
        output.append('\n');
        output.append('\n');
        output.append(" Click on vehicle for info");
    }
    return output;
}

void SceneEdit::getStreet(QGraphicsLineItem* street){
    for(int i = 0; i<streetVector.size(); i++){
        if( streetVector[i]->getStart().getX() == street->line().x1() && streetVector[i]->getEnd().getX() == street->line().x2() && streetVector[i]->getStart().getY() == street->line().y1() && streetVector[i]->getEnd().getY() == street->line().y2() ) {
            if(*PositionOfDelaydedstreet == i){
                streetVector[i]->line->setPen(QPen(QColor(Qt::black),2));
                *PositionOfDelaydedstreet = -1;
                uii.streetName->setText("");
                uii.printDelay->setText("");
            }
            else{
                if(*PositionOfDelaydedstreet != -1)
                {
                    streetVector[*PositionOfDelaydedstreet]->line->setPen(QPen(QColor(Qt::black),2));
                }
                streetVector[i]->line->setPen(QPen(QColor(Qt::red),2));
                uii.streetName->setAlignment(Qt::AlignCenter);
                uii.printDelay->setAlignment(Qt::AlignCenter);
                uii.streetName->setText(streetVector[i]->getName());
                int delay = streetVector[i]->getDelay();
                delay = delay/200;
                if(delay>100){
                    delay = 100;
                }
                uii.printDelay->setText("Delay is on: "+QString::number(delay)+"%");
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
        uii.streetName->setText("");
        uii.printDelay->setText("");
    }
}

void SceneEdit::setLinkInfo()
{
    QString output = "Link -";
    output.append('\n');
    output.append('\n');
    output.append(" Click on vehicle for info");
    this->uii.VehicleData->setFontWeight(3);
    this->uii.VehicleData->setText(output);
    this->uii.VehicleData->setAlignment(Qt::AlignCenter);
    this->uii.TimeTable->setFontWeight(3);
    this->uii.TimeTable->clear();
}

void SceneEdit::resetStreets()
{
    for(int i = 0; i < streetVector.size(); i++)
    {
        streetVector[i]->line->setPen(QPen(QColor(Qt::black),2));
    }
}

void SceneEdit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    for(auto* item: items(event->scenePos()) )
    {
        auto vehicle =  dynamic_cast<QGraphicsEllipseItem*>(item);
        if ( vehicle != nullptr)
        {
            resetStreets();
            resetMarkedLine();
            //qDebug() << "auto" << vehicleVector[0].data()->visual << "kliknuto na" << vehicle;
            uii.VehicleData->setText(printLink(vehicle));
            uii.VehicleData->setAlignment(Qt::AlignCenter);
            return;
        }
        else if(auto street = dynamic_cast<QGraphicsLineItem*>(item); street != nullptr)
        {
            resetStreets();
            getStreet(street);
            setLinkInfo();
            return;
        }
        else
        {
            resetMarkedLine();
            qDebug() << "jinde";
        }
    }
    resetMarkedLine();
    setLinkInfo();
    resetStreets();

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
