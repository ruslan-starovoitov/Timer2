#include "notches.h"


Notches::Notches()
{
    notchesCount = 12;
    notchesColor = new QColor(200,0,255);
    x1 = 70;
    y1 = 0;
    x2 = 96;
    y2 = 0;
}

Notches::Notches(int count, QColor color, int x1, int y1, int x2, int y2)
{
    notchesCount = count;
    notchesColor = &color;
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}


void Notches::draw(QPainter *p)
{
    p->setPen(Qt::NoPen);
    p->setBrush(*notchesColor);
    p->setPen(*notchesColor);

    for(int i = 0; i < notchesCount; i++)
    {
        p->drawLine(x1, y1, x2, y2);
        p->rotate(360/notchesCount);
    }

}
