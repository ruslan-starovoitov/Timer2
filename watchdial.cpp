#include "watchdial.h"

WatchDial::WatchDial()
{
    centerXCoordinateInPercent = 50;
    centerYCoordinateInPercent = 50;

    WatchArrow * watchArrow = new WatchArrow();
    arrows = new WatchArrow[1];
    arrowsCount = 0;
    arrows[arrowsCount++] = *watchArrow;

    notchesCount = 12;
    notchesColor = new QColor(200,0,255);
}

void WatchDial::draw(QPainter *p, long time)
{

}

