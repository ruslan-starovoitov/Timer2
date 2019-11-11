#ifndef WATCHDIAL_H
#define WATCHDIAL_H
#include "notches.h"
#include "watcharrow.h"

//Циферблат
//У циферблата есть насечки и стрелки
class WatchDial
{
public:
    WatchDial();
    ~WatchDial();
    void draw(QPainter *p, long time);

private:
    int centerXCoordinateInPercent;
    int centerYCoordinateInPercent;

    unsigned long long arrowsCount;
    WatchArrow *arrows;

    unsigned long long notchesTypesCount;
    Notches * notches;
};

#endif // WATCHDIAL_H
