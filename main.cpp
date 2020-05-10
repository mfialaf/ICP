/** @brief Imitace dopravních spojů.

    Semestrální projekt - aplikace pro zobrazení linek hromadné dopravy a sledování jejich pohybu.
    @authors Daniel Kamenický xkamen21 & Marek Fiala xfiala60
    @date Květen 2020
    @sub ICP Seminář C++
*/

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
