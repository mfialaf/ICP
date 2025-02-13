/**
  * @file sceneedit.h
  * @authors Daniel Kamenický xkamen21
  * <br/>Marek Fiala xfiala60
  * @details Hlavičkový modul k modulu sceneedit.cpp
  */
#ifndef SCENEEDIT_H
#define SCENEEDIT_H

#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <vehicle.h>
#include <QGraphicsView>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <vehicle.h>
#include <QPen>

class SceneEdit : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SceneEdit(QObject *parent = nullptr);
    SceneEdit(QGraphicsView* view, QVector<Vehicle>* vehicleVector, QVector<Street*> streetVector, Ui::MainWindow* uii, int* PositionOfDelaydedstreet);
    void mouseReleaseEvent2(QMouseEvent *event);
    void mousePressEvent2(QMouseEvent *event);
    void mouseMoveEvent2(QMouseEvent *event);
    QString printLink(QGraphicsEllipseItem* vehicle);
    void getStreet(QGraphicsLineItem* street);
    void resetMarkedLine();
    void setLinkInfo();
    void resetStreets();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QVector<Vehicle>* vehicleVector;
    QVector<Street*> streetVector;
    QGraphicsSceneMouseEvent* ui;
    QGraphicsView* view;
    Ui::MainWindow uii;
    int* PositionOfDelaydedstreet;;
};

#endif // SCENEEDIT_H
