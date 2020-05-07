#include "mainwindow.h"

#include <QApplication>
#include <jsonread.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // MainWindow w;
   // w.show();


    JsonRead file;
    file.ReadJson();
    return a.exec();
}
