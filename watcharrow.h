#ifndef WATCHARROW_H
#define WATCHARROW_H

#include <QtGui>

//Стрелка часов
class WatchArrow
{
public:
    WatchArrow();
    void draw(QPainter *p, int time);

private:
    //Период оборота
    int turnOverPeriod;
    //Полигон
    int pointCount;
    QPoint *polygon;
    QColor color;
};

#endif // WATCHARROW_H
