#ifndef ANALOGCLOCKWINDOW_H
#define ANALOGCLOCKWINDOW_H
#include "dotinfo.h"
#include "rasterwindow.h"
#include "readeriterator.h"
#include <ctime>

#include <QtGui>


///Описывает единственное окно 
class AnalogClockWindow : public RasterWindow
{
    Q_OBJECT
public:
    AnalogClockWindow(const std::string filepath = "data.txt");

protected:
    void timerEvent(QTimerEvent *) override;
    //Отрисовка всей сцены
    void render(QPainter *p) override;
    void mousePressEvent(QMouseEvent *ev) override;
    double getCurrentAngle(long long time);

private:
    int m_timerId;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> prevFrameTime;
    //Пересоздаёт таймер
    int myStartTimer();
    ReaderIterator reader;
    std::list<DotInfo> dots;

};

#endif // ANALOGCLOCKWINDOW_H
