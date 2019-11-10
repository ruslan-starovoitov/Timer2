#include <QtGui>
#include "rasterwindow.h"
#include "analogclockwindow.h"

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    //Тест работы ветки 2
    //Показ окна
    AnalogClockWindow clock;
    clock.show();

    return app.exec();
}
