#ifndef NEJAKYWIDGET_H
#define NEJAKYWIDGET_H

#include <QObject>
#include <QWidget>

class nejakyWidget : public QObject
{
    Q_OBJECT
public:
    explicit nejakyWidget(QObject *parent = nullptr);


protected:

   // virtual void paintEvent(QPaintEvent *event);
    virtual void paintEvent(QPaintEvent *event);

signals:

};

#endif // NEJAKYWIDGET_H
