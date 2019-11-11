#include "notches.h"

#include <QTextStream>


Notches::Notches()
{
    notchesCount = 12;
    notchesColor = new QColor(200,0,255);
    _x1 = 70;
    _y1 = 0;
    _x2 = 96;
    _y2 = 0;

    showInfo();
}

Notches::~Notches()
{
    QTextStream cout(stdout);
    cout<<"Notches object deleted."<<endl;
}

Notches::Notches(int count, QColor * color, int x1, int y1, int x2, int y2)
{
    notchesCount = count;
//    notchesColor = &color;
    notchesColor=color;
    _x1 = x1;
    _y1 = y1;
    _x2 = x2;
    _y2 = y2;

    showInfo();
}

void Notches::showInfo()
{
    QTextStream cout(stdout);
    cout<<"notchesCount ="<<notchesCount<<endl;
    cout<<"_x1 ="<<_x1<<endl;
    cout<<"_y1 ="<<_y1<<endl;
    cout<<"_x2 ="<<_x2<<endl;
    cout<<"_y2 ="<<_y2<<endl;
    cout<<"notchesColor ="<<notchesColor->red()<<" "<<notchesColor->green()<<" "<<notchesColor->blue()<<endl;

}
void Notches::draw(QPainter *p)
{
    p->setPen(Qt::NoPen);
    p->setBrush(*notchesColor);
    p->setPen(*notchesColor);

    for(int i = 0; i < notchesCount; i++)
    {
        p->drawLine(_x1, _y1, _x2, _y2);
        p->rotate(360/notchesCount);
    }

}
