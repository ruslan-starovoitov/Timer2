#include <QApplication>
#include "analogclockwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    std::string filepath;
    if(argc > 1){
        filepath = std::string(argv[1]);
    }
    else {
        filepath = "./data.txt";
    }
    AnalogClockWindow w(filepath);
    w.show();
    return app.exec();

}
