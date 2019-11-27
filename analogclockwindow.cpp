#include "analogclockwindow.h"
#include <ctime>
#include <QWidget>
#include <math.h>

const int fps = 100.0;

AnalogClockWindow::AnalogClockWindow()
{
    setTitle("Radar");
    resize(200, 200);

    reader = ReaderIterator();
    startTime = std::chrono::high_resolution_clock::now();

    m_timerId = myStartTimer();
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

double AnalogClockWindow::getCurrentAngle(long long time)
{
    int period =10;
    return ((time %(period*1000)) / period) * M_PI * 2/1000;
}

void AnalogClockWindow::render(QPainter *p)
{
    p->translate(width() / 2, height() / 2);

    int side = qMin(width(), height());
    p->scale(side / 200.0, side / 200.0);

    //Сглаживание
    p->setRenderHint(QPainter::Antialiasing);

    p->setPen(Qt::NoPen);
    p->setBrush(Qt::black);
    p->drawRect(-100, -100, 200, 200);

    //Вычисление времени
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(now-startTime).count();


    double sec = duration/1000000000.0;
    //от 0 до 1
    double percents = sec/10;
    double angle = 360*percents;
    p->save();
    p->rotate(-90);
    p->rotate(angle);

    QConicalGradient conicalGrad(0, 0, 0);
    conicalGrad.setColorAt(0, Qt::green);
    conicalGrad.setColorAt(0.125, Qt::transparent);
    p->setBrush(QBrush(conicalGrad));
    p->drawPie(-100, -100, 200, 200, 0, 1000);
    p->restore();



    auto planeInfo = reader.GetCurrent();

    auto deltaT = planeInfo->timeMs - duration / 1000000;
    if(abs(deltaT) < 10)
    {
        int transparency = 0;
        if(deltaT > 0) transparency = deltaT * 255 / 1000;
        auto color = QColor(0, 255, 0, transparency);
        p->setPen(QPen(color, 3));
        qreal x = planeInfo->radius / 150000 * sin(angle / 180 * M_PI) * 100;
        qreal y = planeInfo->radius / 150000 * cos(angle / 180 * M_PI) * 100;
        p->drawPoint(QPointF(x, y));
        reader.MoveNext();
    }

    p->end();
}

void AnalogClockWindow::mousePressEvent(QMouseEvent *ev)
{
    qInfo() << ev->x() << " " << ev->y();
}

