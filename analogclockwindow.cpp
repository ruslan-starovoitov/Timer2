#include "analogclockwindow.h"
#include <ctime>
#include <QWidget>
#include <math.h>

const int fps = 100.0;

AnalogClockWindow::AnalogClockWindow(const std::string filepath) : reader(filepath)
{
    setTitle("Radar");
    resize(500, 500);

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

    p->save();
    p->setPen(QPen(QColor(0, 255, 0, 150), 1));
    p->setBrush(Qt::NoBrush);
    p->drawEllipse(-100, -100, 200, 200);
    p->drawEllipse(-50, -50, 100, 100);
    p->restore();

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
    conicalGrad.setColorAt(0.005, QColor(0, 255, 0, 100));
    conicalGrad.setColorAt(0.125, Qt::transparent);
    p->setBrush(QBrush(conicalGrad));
    p->drawPie(-100, -100, 200, 200, 0, 1000);
    p->restore();



    auto planeInfo = reader.GetCurrent();

    if(planeInfo != nullptr)
    {
        auto deltaT = planeInfo->timeMs - duration / 1000000;
        const int maxDelta = 10;
        if(abs(deltaT) < maxDelta)
        {
            int transparency = 0;
            if(deltaT > 0) transparency = deltaT * 255 / maxDelta;
            qInfo() << transparency;
            auto color = QColor(0, 255, 0, transparency);
            qInfo() << color;
            p->setPen(QPen(color, 3));
            p->setBrush(color);
            qreal x = planeInfo->radius / 150000 * sin((angle) / 180 * M_PI) * 100;
            qreal y = planeInfo->radius / 150000 * cos((angle) / 180 * M_PI) * 100;
            qInfo()<< "X: " << x << " Y: " << y;
            p->drawPoint(QPointF(x, y));
            qInfo() << "Before MoveNext";
            reader.MoveNext();
            qInfo() << "After MoveNext";
        }
    }

    p->end();
}

void AnalogClockWindow::mousePressEvent(QMouseEvent *ev)
{
    qInfo() << ev->x() << " " << ev->y();
}

