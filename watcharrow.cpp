#include "watcharrow.h"
#include <QTextStream>
using namespace std;

WatchArrow::WatchArrow()
{
    turnOverPeriod= 60;
    color = new QColor(17,255,0);
    pointCount = 3;
    polygon = new QPoint[3];
    polygon[0] = QPoint(-1, 0);
    polygon[1] = QPoint(1, 0);
    polygon[2] = QPoint(0, -95);
}



WatchArrow::WatchArrow(int turnOverPeriod, QColor color, int pointCount, QPoint *polygon)
{
    this->turnOverPeriod= turnOverPeriod;
    this->color = &color;
    this->pointCount = pointCount;
    this->polygon = polygon;
}


void WatchArrow::draw(QPainter *p, int time)
{
    QTextStream cout(stdout);

    try {
        if(pointCount==0 || polygon==nullptr||polygon->isNull()){
            throw "polygon is empty";
        }
    } catch (const char * ex) {
        cout<<"Exception: "<<ex<<endl;
    }

    double angle = 6*(time%turnOverPeriod)/(turnOverPeriod/60);

    p->setPen(Qt::NoPen);
    p->setBrush(*color);
    p->save();
    p->rotate(angle);
    p->drawConvexPolygon(polygon, pointCount);
    p->restore();
}


