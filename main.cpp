#include <QtGui>
#include "rasterwindow.h"
#include "analogclockwindow.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char **argv)
{
//    QGuiApplication app(argc, argv);

//    AnalogClockWindow clock;
//    clock.show();


//    return app.exec();

    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();

}
