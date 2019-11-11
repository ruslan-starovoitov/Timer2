#include "analogclockwindow.h"
#include <ctime>
#include <QWidget>

const int fps = 30.0;

AnalogClockWindow::AnalogClockWindow()
{
    watchDialsCount=2;
    watchDials = new WatchDial[watchDialsCount]{
                WatchDial(),
                WatchDial(50, 30, 1,
                          new WatchArrow[1]{
                                        WatchArrow(3600, new QColor(0,0,0), 4, new QPoint[4]{QPoint(-1,0),QPoint(1,0),QPoint(1,-20),QPoint(-1,-20),})
                          },
                1, new Notches[1]{
                    Notches (12, new QColor(0,0,0), 20,0,25,0)
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
            begin += pauseTime - begin;
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

    //Перенос системы координат для циферблата
    //p->translate(width() / 2, height() / 2);

    //Для масштабирования
//    int side = qMin(width(), height());
//    p->scale(side / 200.0, side / 200.0);

    time_t seconds;
    seconds = time (NULL);
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(now-begin).count();

    //Отрисовка циферблатов
    for(int i = 0; i < watchDialsCount; i++){
        watchDials[i].draw(p, duration, width(), height());
    }
    p->end();


}

