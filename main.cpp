#include <QtGui>
#include "rasterwindow.h"
#include "analogclockwindow.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char **argv)
{

    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();

}
