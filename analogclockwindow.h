#ifndef ANALOGCLOCKWINDOW_H
#define ANALOGCLOCKWINDOW_H
#include "rasterwindow.h"
#include "watchdial.h"
#include <QtGui>

enum TimerStates { Reseted, Paused, Started };

///Описывает единственное окно 
class AnalogClockWindow : public RasterWindow
{
    Q_OBJECT
public:
    AnalogClockWindow();
    void startStop();
    void reset();

protected:
    void timerEvent(QTimerEvent *) override;
    //Отрисовка всей сцены
    void render(QPainter *p) override;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> begin;
    std::chrono::time_point<std::chrono::high_resolution_clock> pauseTime;
    int m_timerId;
    TimerStates timerState;
    //Пересоздаёт таймер
    int myStartTimer();

    int watchDialsCount;
    WatchDial * watchDials;
    QPushButton *m_button;

signals:
    void timeChanged(long long time);
};

#endif // ANALOGCLOCKWINDOW_H
