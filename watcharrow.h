#ifndef WATCHARROW_H
#define WATCHARROW_H

#include <QtGui>

//Стрелка часов
class WatchArrow
{
public:
    WatchArrow();
    void draw(QPainter *p, float angle);
    double getSpeed();

private:
    double speed;
    int pointCount;
    QPoint *polygon;
    QColor color;
};

#endif // WATCHARROW_H
