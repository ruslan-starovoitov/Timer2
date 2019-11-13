#include "analogclockwindow.h"
#include <ctime>
#include <QWidget>

const int fps = 100.0;

AnalogClockWindow::AnalogClockWindow()
{
    watchDialsCount=3;
    int _arrsCount = 1360;
    WatchArrow *arrows = new WatchArrow[_arrsCount];
    for(int i = 0; i < _arrsCount; i++){
        arrows[i] = WatchArrow(i, new QColor(i * 10 % 255,255,i * i % 256), 3, new QPoint[3]{QPoint(-1, 0),QPoint(1, 0),QPoint(0,-30)});
    }

    watchDials = new WatchDial[watchDialsCount]{
                WatchDial(),
                WatchDial(50, 30, 2,
                          new WatchArrow[2]{
                                        WatchArrow(1, new QColor(0,0,0), 3, new QPoint[3]{QPoint(-1,0),QPoint(1,0),QPoint(0,-20)}),
                                        WatchArrow(60, new QColor(0,255,0), 3, new QPoint[3]{QPoint(-3,-30),QPoint(3,-30),QPoint(0,-20)})
                          },
                1, new Notches[1]{
                    Notches (12, new QColor(0,0,0), 20,0,25,0)
                } ),
                WatchDial(50, 70, _arrsCount,
                          arrows,
                1, new Notches[1]{
                    Notches (60, new QColor(90,110,50), 20,0,25,0)
                } )
    };

    setTitle("Analog Clock");
    resize(200, 200);

    timerState = Paused;
    reset();
}


int AnalogClockWindow::myStartTimer(){
    return startTimer(1000 / fps);
}
void AnalogClockWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timerId)
    {
        renderLater();
    }
}

void AnalogClockWindow::startStop()
{
    switch (timerState) {
        case Reseted:
            timerState = Started;
            m_timerId = myStartTimer();
            begin = std::chrono::high_resolution_clock::now();
            pauseTime = begin;
            break;
        case Started:
            timerState = Paused;
            killTimer(m_timerId);
            pauseTime = std::chrono::high_resolution_clock::now();
            break;
        case Paused:
            timerState = Started;
            m_timerId = myStartTimer();
            auto now = std::chrono::high_resolution_clock::now();
            begin += now-pauseTime;
            renderLater();
            break;
    }
}

void AnalogClockWindow::reset()
{
    if(timerState == Paused){
        timerState = Reseted;
        begin = std::chrono::high_resolution_clock::now();
        pauseTime = begin;
        renderLater();
    }
}


void AnalogClockWindow::render(QPainter *p)
{
    //Сглаживание
    p->setRenderHint(QPainter::Antialiasing);

    //Вычисление времени
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(now-begin).count();

    switch (timerState) {
        case Reseted:
            duration = 0;
            break;
        case Paused:
            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(pauseTime-begin).count();
            break;
    }

    //
    emit timeChanged(duration);
    //Отрисовка циферблатов
    for(int i = 0; i < watchDialsCount; i++){
        watchDials[i].draw(p, duration, width(), height());
    }
    p->end();
}

