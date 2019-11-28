#include "radarwindow.h"
#include <ctime>
#include <QWidget>
#include <math.h>

const int fps = 100.0;

RadarWindow::RadarWindow(const std::string filepath) : reader(filepath), period(10), maxRadius(150000), deltaScale(0.01)
{
    setTitle("Radar");
    resize(500, 500);

    startTime = std::chrono::high_resolution_clock::now();
    prevFrameTime = startTime;
    scale = 1.0;
    m_timerId = myStartTimer();
}


int RadarWindow::myStartTimer(){
    return startTimer(1000 / fps);
}
void RadarWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timerId)
    {
        renderLater();
    }
}

double RadarWindow::getCurrentAngle(long long time)
{
    int period =10;
    return ((time %(period*1000)) / period) * M_PI * 2/1000;
}

void RadarWindow::render(QPainter *p)
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
    long long renderDelta = std::chrono::duration_cast<std::chrono::milliseconds>(now-prevFrameTime).count();
    prevFrameTime = now;

    double sec = duration/1000000000.0;
    //от 0 до 1
    double percents = sec/period;
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

    p->setPen(QPen(Qt::green, 1));
    QFont font = p->font();
    font.setPointSize(3);
    p->setFont(font);
    p->drawText(0, 100, QString::number(maxRadius / scale));
    p->drawText(0, 50, QString::number(maxRadius / scale / 2.0));

    p->scale(scale, scale);

    for(DotInfo &dot : dots)
    {
        if(abs(dot.x) * scale <= 100 && abs(dot.y) * scale <= 100)
        {
            int transparency = (255 * dot.timeToFade) / dot.fadingTime;
            auto color = QColor(0, 255, 0, transparency);
            p->setPen(QPen(color, 1));
            p->drawPoint(QPointF(dot.x, dot.y));
        }
        dot.timeToFade -= renderDelta;
        if(dot.timeToFade <= 0)
        {
            dots.pop_front();
        }
    }

    if(reader.HasValue())
    {
        PlaneInfo* planeInfo = reader.GetCurrent();

        long long deltaT = planeInfo->timeMs - duration / 1000000;

        while(planeInfo != nullptr && deltaT <= 0)
        {
            if(deltaT > -500)
            {
                double planeAngle = 2 * M_PI * planeInfo->timeMs / 1000 / period;
                //qInfo()<< planeAngle;
                qreal x = planeInfo->radius / maxRadius * sin(planeAngle) * 100;
                qreal y = planeInfo->radius / maxRadius * cos(planeAngle) * 100;
                //qInfo()<< "X: " << x << " Y: " << y;
                reader.MoveNext();

                DotInfo info;
                info.x = x;
                info.y = -y;
                info.height = planeInfo->height;
                info.velocity = planeInfo->velocity;
                info.index = planeInfo->index;
                info.timeToFade += deltaT;

                dots.push_back(info);
            }
            else
            {
                qInfo() << "Был пропущен самолёт.";
                reader.MoveNext();
            }

            if(!reader.HasValue()) break;

            planeInfo = reader.GetCurrent();
            deltaT = planeInfo->timeMs - duration / 1000000;
        }
    }
    else
    {
        qInfo() << "Отсутствует текущее значение. Возможно, закончился файл.";
    }

    p->end();
}

void RadarWindow::mousePressEvent(QMouseEvent *ev)
{
    qInfo() << ev->x() << " " << ev->y();
}

void RadarWindow::wheelEvent(QWheelEvent *ev)
{
    scale += ev->delta() / 120.0 * deltaScale;
    if(scale < deltaScale){
        scale = deltaScale;
    }
}

