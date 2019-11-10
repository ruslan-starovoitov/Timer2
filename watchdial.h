#ifndef WATCHDIAL_H
#define WATCHDIAL_H
#include "watcharrow.h"

//Циферблат
//У циферблата есть насечки и стрелки
class WatchDial
{
public:
    WatchDial();
    void draw(QPainter *p, long time);

private:
    int centerXCoordinateInPercent;
    int centerYCoordinateInPercent;

    int arrowsCount;
    WatchArrow *arrows;

    int notchesCount;
    QColor notchesColor;
};

#endif // WATCHDIAL_H
