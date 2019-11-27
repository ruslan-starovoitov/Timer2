#ifndef ANALOGCLOCKWINDOW_H
#define ANALOGCLOCKWINDOW_H
#include "rasterwindow.h"
#include "readeriterator.h"
#include <ctime>

#include <QtGui>


///Описывает единственное окно 
class AnalogClockWindow : public RasterWindow
{
    Q_OBJECT
public:
    AnalogClockWindow();

protected:
    void timerEvent(QTimerEvent *) override;
    //Отрисовка всей сцены
    void render(QPainter *p) override;
    void mousePressEvent(QMouseEvent *ev) override;
    double getCurrentAngle(long long time);

private:
    int m_timerId;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    //Пересоздаёт таймер
    int myStartTimer();
    ReaderIterator reader;

};

#endif // ANALOGCLOCKWINDOW_H
