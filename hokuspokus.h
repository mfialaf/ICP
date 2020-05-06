#ifndef HOKUSPOKUS_H
#define HOKUSPOKUS_H

#include <QWidget>

class hokusPokus : public QWidget
{
    Q_OBJECT
public:
    explicit hokusPokus(QWidget *parent = nullptr);

protected:
   // virtual void paintEvent(QPaintEvent *event) override();

    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override; // vzdy psat override, predefinovavam chovani bazove tirdy


signals:

};

#endif // HOKUSPOKUS_H
