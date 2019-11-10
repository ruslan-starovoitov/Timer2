#include "watcharrow.h"

WatchArrow::WatchArrow()
{
    turnOverPeriod= 60;


    color = new QColor(17,255,0);

    pointCount = 3;
    QPoint minuteHand[3] = {
            QPoint(-1, 0),
            QPoint(1, 0),
            QPoint(0, -95)
        };
    polygon = minuteHand;
}


void WatchArrow::draw(QPainter *p, int time)
{
   throw 166;
}
