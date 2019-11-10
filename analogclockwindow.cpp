#include "analogclockwindow.h"

const int fps = 30.0;

AnalogClockWindow::AnalogClockWindow()
{
    setTitle("Analog Clock");
    resize(200, 200);

    angle = 0;
    m_timerId = myStartTimer();
    timerState = Started;
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
    switch (timerState) {
        case Reseted:
            timerState = Started;
            m_timerId = myStartTimer();
            break;
        case Started:
            timerState = Paused;
            killTimer(m_timerId);
            break;
        case Paused:
            timerState = Reseted;
            angle = 0;
            renderLater();
            break;
    }
}


void AnalogClockWindow::render(QPainter *p)
{
    //Сглаживание
    p->setRenderHint(QPainter::Antialiasing);

    //Полигон стрелки
    static const QPoint minuteHand[3] = {
        QPoint(-1, 0),
        QPoint(1, 0),
        QPoint(0, -95)
    };    

    //Перенос системы координат для циферблата
    p->translate(width() / 2, height() / 2);

    //Для масштабирования
    int side = qMin(width(), height());
    p->scale(side / 200.0, side / 200.0);

    //Отрисовка насечек для часов
    QColor blueColor(3, 15, 252);
    p->setPen(Qt::NoPen);
    p->setBrush(blueColor);
    p->setPen(blueColor);
    for (int i = 0; i < 12; ++i) {
        p->drawLine(70, 0, 96, 0);
        p->rotate(30.0);
    }

    //Отрисовка стрелки
    QColor orangeColor(252,61,3);
    p->setPen(Qt::NoPen);    
    p->setBrush(orangeColor);

    p->save();
    p->rotate(angle);
    p->drawConvexPolygon(minuteHand, 3);
    p->restore();

    //Отрисовка насечек для минут
    QColor redColor(252,3,15);
    p->setPen(redColor);
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            p->drawLine(80, 0, 96, 0);
        p->rotate(6.0);
    }
}

