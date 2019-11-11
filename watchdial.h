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
    WatchDial(int centerXCoordinateInPercent, int centerYCoordinateInPercent, int arrowsCount, WatchArrow *arrows, int notchesCount, Notches *notches);
    WatchDial(int centerXCoordinateInPercent, int centerYCoordinateInPercent);
    ~WatchDial();
    void draw(QPainter *p, long long time, int windowWidth, int windowHeight);
private:
    int _centerXCoordinateInPercent;
    int _centerYCoordinateInPercent;

    unsigned long long _arrowsCount;
    WatchArrow *_arrows;

    unsigned long long _notchesTypesCount;
    Notches * _notches;
};

#endif // WATCHDIAL_H
