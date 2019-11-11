#include "watcharrow.h"
#include <QTextStream>
using namespace std;
#include <sstream>

WatchArrow::WatchArrow()
{
    _turnOverPeriod= 60;
    _color = new QColor(17,255,0);
    _pointCount = 3;
    _polygon = new QPoint[3];
    _polygon[0] = QPoint(-1, 0);
    _polygon[1] = QPoint(1, 0);
    _polygon[2] = QPoint(0, -95);

    //Внешняя стрелка
//    _polygon[0] = QPoint(-5, -100);
//    _polygon[1] = QPoint(5, -100);
//    _polygon[2] = QPoint(0, -90);

    printInfo();
}



WatchArrow::WatchArrow(int turnOverPeriod)
{
    _turnOverPeriod= turnOverPeriod;
    _color = new QColor(17,255,0);
    _pointCount = 3;
    _polygon = new QPoint[3];
    _polygon[0] = QPoint(-1, 0);
    _polygon[1] = QPoint(1, 0);
    _polygon[2] = QPoint(0, -95);

    printInfo();
}



WatchArrow::WatchArrow(int turnOverPeriod, QColor * color, int pointCount, QPoint *polygon)
{
    _turnOverPeriod= turnOverPeriod;
    _color = color;
    _pointCount = pointCount;
    _polygon = polygon;



    if(_pointCount<3 || _polygon==nullptr||_polygon->isNull()){
        std::stringstream ss;
        ss << "unable to create arrow object. Point count = " + std::to_string( _pointCount  ) << std::endl;
        throw std::runtime_error(ss.str());
    }


    if(_turnOverPeriod<1){
        std::stringstream ss;
        ss << "unable to create arrow object. turnOverPeriod = " + std::to_string( _turnOverPeriod  ) << std::endl;
        throw std::runtime_error(ss.str());
    }

    printInfo();


}

void WatchArrow::printInfo()
{
    QTextStream cout(stdout);
    cout<<"Arrow object created."<<endl;
    cout<<"Point count = "<<_pointCount<<endl;
    cout<<"Turnover period = "<<_turnOverPeriod<<endl;
    for(int i =0; i < _pointCount; i++)
    {
        cout<<  "Point \t\tx= "<<_polygon[i].x()<<"\t\t y= "<<_polygon[i].y()<<endl;
    }
}

void WatchArrow::draw(QPainter *p, long long time)
{
    QTextStream cout(stdout);

    try {
        if(_pointCount==0 || _polygon==nullptr||_polygon->isNull()){
            std::stringstream ss;
            ss << "polygon is empty. Point count = " + std::to_string( _pointCount  ) << std::endl;
            throw std::runtime_error(ss.str());
        }
    } catch (const char * ex) {
        cout<<"Exception: "<<ex<<endl;
    }

    double sec = time/1000000000.0;
    //от 0 до 1
    double percents = sec/_turnOverPeriod;
    double angle = 360*percents;

//    cout<<"sec = "<<sec<<endl;
//    cout<<"percents = "<<percents<<endl;
//    cout<<"angle = "<<angle<<endl;

    p->setPen(Qt::NoPen);
    p->setBrush(*_color);
    p->save();
    p->rotate(angle);
    p->drawConvexPolygon(_polygon, _pointCount);
    p->restore();
}

WatchArrow::~WatchArrow()
{
    QTextStream cout(stdout);
    cout<<"WatchArrow object deleted."<<endl;
}


