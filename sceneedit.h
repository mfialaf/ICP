#ifndef SCENEEDIT_H
#define SCENEEDIT_H

#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsLineItem>
#include <QMouseEvent>
#include <vehicle.h>
#include <QGraphicsView>

class SceneEdit : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SceneEdit(QObject *parent = nullptr);
    SceneEdit(QGraphicsView* view, QVector<Vehicle>* vehicleVector);
    void mouseReleaseEvent2(QMouseEvent *event);
    void mousePressEvent2(QMouseEvent *event);
    void mouseMoveEvent2(QMouseEvent *event);
    void printLink(QGraphicsEllipseItem* vehicle);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:

private:
    QVector<Vehicle>* vehicleVector;
    QGraphicsSceneMouseEvent* ui;
    QGraphicsView* view;
};

#endif // SCENEEDIT_H
