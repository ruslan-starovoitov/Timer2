#include "analogclockwindow.h"

const float fps = 30.0;

AnalogClockWindow::AnalogClockWindow()
{
    setTitle("Analog Clock");
    resize(200, 200);

    angle = 0;
    m_timerId = startTimer(1000.0 / fps);
    timerState = Started;
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
            m_timerId = startTimer(1000 / fps);
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

    static const QPoint minuteHand[4] = {
        QPoint(-1, 0),
        QPoint(1, 0),
        QPoint(0.5, -95),
        QPoint(-0.5, -95)
    };

    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);

    p->setRenderHint(QPainter::Antialiasing);


    p->translate(width() / 2, height() / 2);

    int side = qMin(width(), height());
    p->scale(side / 200.0, side / 200.0);

    p->setPen(Qt::NoPen);
    p->setBrush(hourColor);
    p->setPen(hourColor);

    for (int i = 0; i < 12; ++i) {
        p->drawLine(70, 0, 96, 0);
        p->rotate(30.0);
    }
    p->setPen(Qt::NoPen);
    p->setBrush(minuteColor);

    p->save();
    p->rotate(angle);
    p->drawConvexPolygon(minuteHand, 4);
    p->restore();

    p->setPen(minuteColor);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            p->drawLine(80, 0, 96, 0);
        p->rotate(6.0);
    }
}

