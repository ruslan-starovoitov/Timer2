#ifndef ANALOGCLOCKWINDOW_H
#define ANALOGCLOCKWINDOW_H
#include "rasterwindow.h"
#include <QtGui>

enum TimerStates { Reseted, Paused, Started };

///Описывает единственное окно 
class AnalogClockWindow : public RasterWindow
{
public:
    AnalogClockWindow();

protected:
    void timerEvent(QTimerEvent *) override;
    void render(QPainter *p) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    int m_timerId;
    float angle;
    TimerStates timerState;
};

#endif // ANALOGCLOCKWINDOW_H
