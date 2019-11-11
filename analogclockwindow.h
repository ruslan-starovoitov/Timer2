#ifndef ANALOGCLOCKWINDOW_H
#define ANALOGCLOCKWINDOW_H
#include "rasterwindow.h"
#include "watchdial.h"
#include <QtGui>

enum TimerStates { Reseted, Paused, Started };

///Описывает единственное окно 
class AnalogClockWindow : public RasterWindow
{
//    Q_OBJECT
public:
    AnalogClockWindow();

protected:
    void timerEvent(QTimerEvent *) override;
    //Отрисовка всей сцены
    void render(QPainter *p) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
 void handleButton();

private:
    int m_timerId;
    double angle;
    TimerStates timerState;
    //Пересоздаёт таймер
    int myStartTimer();

    int watchDialsCount;
    WatchDial * watchDials;
    QPushButton *m_button;
};

#endif // ANALOGCLOCKWINDOW_H
