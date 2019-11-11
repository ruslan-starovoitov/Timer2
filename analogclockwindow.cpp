#include "analogclockwindow.h"
#include <ctime>
#include <QWidget>

const int fps = 30.0;
const auto begin1 = std::chrono::high_resolution_clock::now();

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


    angle = 0;
    m_timerId = myStartTimer();
    timerState = Started;



    m_rbutton = new RasterButton (new QColor(0,0,0), "Zrada", 0, 0, 25, 50);
}


int AnalogClockWindow::myStartTimer(){
    return startTimer(1000 / fps);
}
void AnalogClockWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timerId)
    {
        angle += 6.0 / fps;
        if(angle >= 360.0) angle -= 360.0;
        renderLater();
    }
}

void AnalogClockWindow::mousePressEvent(QMouseEvent *event)
{
//    switch (timerState) {
//        case Reseted:
//            timerState = Started;
//            m_timerId = myStartTimer();
//            break;
//        case Started:
//            timerState = Paused;
//            killTimer(m_timerId);
//            break;
//        case Paused:
//            timerState = Reseted;
//            angle = 0;
//            renderLater();
//            break;
//    }
}

void AnalogClockWindow::mouseMoveEvent(QMouseEvent *event)
{

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
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(now-begin1).count();

    //Отрисовка циферблатов
    for(int i = 0; i < watchDialsCount; i++){
        watchDials[i].draw(p, duration, width(), height());
    }

    m_rbutton->draw(p);

    p->end();


}

