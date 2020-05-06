#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:
    void onValueChanged(int val); // kdyz zde mam ukazatel tak alt + Enter mi vyvori deklaraci te funkce

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
