#include <QtGui>
#include "rasterwindow.h"
#include "analogclockwindow.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);    

    AnalogClockWindow clock;
    clock.show();
    return app.exec();

}
