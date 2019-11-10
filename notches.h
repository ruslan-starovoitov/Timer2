#ifndef NOTCHES_H
#define NOTCHES_H

#include <QPainter>



class Notches
{
public:
    Notches();
    void draw(QPainter *p);
    Notches(int count, QColor color, int x1, int y1, int x2, int y2);
private:
    QColor *notchesColor;
    int notchesCount;
    int x1;
    int y1;
    int x2;
    int y2;
};

#endif // NOTCHES_H
