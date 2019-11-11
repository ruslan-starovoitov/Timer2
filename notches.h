#ifndef NOTCHES_H
#define NOTCHES_H

#include "notch.h"

#include <QPainter>



class Notches
{
public:
    Notches();
    ~Notches();
    void draw(QPainter *p);
    void showInfo();
    Notches(int count, QColor *color, int x1, int y1, int x2, int y2);
private:
    QColor *notchesColor;
    unsigned long long notchesCount;
    int _x1;
    int _y1;
    int _x2;
    int _y2;
    Notch * specialNotches;
    int specialNotchesCount;
};

#endif // NOTCHES_H
