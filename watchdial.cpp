#include "watchdial.h"

WatchDial::WatchDial()
{
    centerXCoordinateInPercent = 50;
    centerYCoordinateInPercent = 50;

    arrowsCount = 2;
    arrows =  new WatchArrow [arrowsCount]{
            WatchArrow(),
            WatchArrow(3600, new QColor(120, 120,0), 4, new QPoint[4]{QPoint(1,0),QPoint(-1,0),QPoint(-1,-50),QPoint(1,-50)})
        };


    notchesTypesCount = 2;
    notches= new Notches[notchesTypesCount]{
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

void WatchDial::draw(QPainter *p, long time)
{
    QTextStream cout(stdout);


    //Отрисовка насечек
    for(int i = 0; i < notchesTypesCount; i++){
        notches[i].draw(p);
    }


    //Отрисовка стрелок
    for(int i = 0; i < arrowsCount; i++)
    {
        //Отрисовать стрелку
        arrows[i].draw(p, time);
    }
}

