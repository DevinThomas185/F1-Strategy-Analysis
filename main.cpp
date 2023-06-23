#include "mainwindow.h"

#include <QApplication>
#include <QThread>
#include <iostream>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowState(Qt::WindowFullScreen);

    w.show();
    return a.exec();
}

