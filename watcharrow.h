#ifndef WATCHARROW_H
#define WATCHARROW_H

#include <QtGui>

//Стрелка часов
class WatchArrow
{
public:
    WatchArrow();
    void draw(QPainter *p, long long time);

    WatchArrow(int _turnOverPeriod, QColor * _color, int _pointCount, QPoint *_polygon);
    WatchArrow(int _turnOverPeriod);
    void printInfo();
    ~WatchArrow();
private:
    //Период оборота
    int _turnOverPeriod;
    //Полигон
    int _pointCount;
    QPoint *_polygon;
    QColor *_color;
};

#endif // WATCHARROW_H
