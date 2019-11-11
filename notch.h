#ifndef NOTCH_H
#define NOTCH_H

#include <QPainter>



class Notch
{
public:
    void draw(QPainter *p);
    Notch(int x1, int y1, int x2, int y2, QColor *color, double angle);
private:
    int x1;
    int y1;
    int x2;
    int y2;
    double angle;
    QColor *color;
};

#endif // NOTCH_H
