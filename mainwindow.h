#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    // POkud chci mit objekt co vysila signaly musi to dedit z QObject

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void signalChanged(int val);

public slots:
    void TimeUpdate();

private slots:
    void zoom(int val); // kdyz zde mam ukazatel tak alt + Enter mi vyvori deklaraci te funkce

private:
    Ui::MainWindow *ui;
    QTimer *timer;
};
#endif // MAINWINDOW_H
