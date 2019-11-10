#ifndef WATCHDIAL_H
#define WATCHDIAL_H
#include "watcharrow.h"

//Циферблат
class WatchDial
{
public:
    WatchDial();
    void draw(QPainter *p, long time);

private:
    int arrowsCount;
    WatchArrow *arrows;
};

#endif // WATCHDIAL_H
