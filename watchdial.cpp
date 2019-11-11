#include "watchdial.h"

WatchDial::WatchDial()
{
    _centerXCoordinateInPercent = 50;
    _centerYCoordinateInPercent = 50;

    _arrowsCount = 1;
    _arrows =  new WatchArrow [_arrowsCount]{
            WatchArrow()
//                    ,            WatchArrow(3600, new QColor(120, 120,0), 4, new QPoint[4]{QPoint(1,0),QPoint(-1,0),QPoint(-1,-50),QPoint(1,-50)})
        };


    _notchesTypesCount = 1;
    _notches= new Notches[_notchesTypesCount]{
        Notches ()
//        ,Notches (24, new QColor(255,2,2), 40,0,50,0)
    };


    QTextStream cout(stdout);
    cout<<"WatchDial object created."<<endl;
}

WatchDial::WatchDial(int centerXCoordinateInPercent,
                     int centerYCoordinateInPercent,
                     int arrowsCount,
                     WatchArrow * arrows,
                     int notchesCount,
                     Notches * notches )
{
    _centerXCoordinateInPercent = centerXCoordinateInPercent;
    _centerYCoordinateInPercent = centerYCoordinateInPercent;

    //TODO тут нужны проверки на длинну массива

    _arrowsCount = arrowsCount;
    _arrows =  arrows;

    _notchesTypesCount = notchesCount;
    _notches= notches;

    QTextStream cout(stdout);
    cout<<"WatchDial object created."<<endl;
}

WatchDial::WatchDial(int centerXCoordinateInPercent, int centerYCoordinateInPercent)
{
    _centerXCoordinateInPercent = centerXCoordinateInPercent;
    _centerYCoordinateInPercent = centerYCoordinateInPercent;

    _arrowsCount = 2;
    _arrows =  new WatchArrow [_arrowsCount]{
            WatchArrow(),
            WatchArrow(3600, new QColor(120, 120,0), 4, new QPoint[4]{QPoint(1,0),QPoint(-1,0),QPoint(-1,-50),QPoint(1,-50)})
        };


    _notchesTypesCount = 2;
    _notches= new Notches[_notchesTypesCount]{
        Notches (),
        Notches (24, new QColor(255,2,2), 40,0,50,0)
    };


    QTextStream cout(stdout);
    cout<<"WatchDial object created."<<endl;
}


WatchDial::~WatchDial()
{
    QTextStream cout(stdout);
    cout<<"WatchDial object deleted."<<endl;
}

void WatchDial::draw(QPainter *p, long time, int windowWidth,int windowHeight)
{
    QTextStream cout(stdout);

    p->save();

    //Перенос системы координат для циферблата
    p->translate(windowWidth *_centerXCoordinateInPercent/100, windowHeight *_centerYCoordinateInPercent/100);

    //Масштабирование
    int side = qMin(windowWidth, windowHeight);
    p->scale(side / 200.0, side / 200.0);

    //Отрисовка насечек
    for(int i = 0; i < _notchesTypesCount; i++){
        _notches[i].draw(p);
    }


    //Отрисовка стрелок
    for(int i = 0; i < _arrowsCount; i++)
    {
        //Отрисовать стрелку
        _arrows[i].draw(p, time);
    }


    p->restore();
}

