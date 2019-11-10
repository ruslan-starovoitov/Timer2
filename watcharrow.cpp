#include "watcharrow.h"

WatchArrow::WatchArrow()
{
    speed = 6.0;
    pointCount = 4;
    polygon =  new QPoint[pointCount] {
        QPoint(-1, 0),
        QPoint(1, 0),
        QPoint(0.5, -95),
        QPoint(-0.5, -95)
    };
    color = QColor(0, 127, 127, 191);
}

double WatchArrow::getSpeed()
{
    return speed;
}

void WatchArrow::draw(QPainter *p, float angle)
{
    p->setPen(Qt::NoPen);
    p->setBrush(color);
    p->rotate(angle);
    p->drawConvexPolygon(polygon, pointCount);
}
