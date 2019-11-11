#include "notch.h"

Notch::Notch(int x1,int y1, int x2, int y2, QColor * color, double angle)
{
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
    this->color = color;
    this->angle = angle;
}

void Notch::draw(QPainter *p)
{
    p->setPen(Qt::NoPen);
    p->setBrush(*color);
    p->setPen(*color);

    //Рисование одной насечки
    p->rotate(0);
    p->rotate(angle);
    p->drawLine(x1, y1, x2, y2);
    p->rotate(0);
}
