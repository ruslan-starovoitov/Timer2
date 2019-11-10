#include "watchdial.h"

WatchDial::WatchDial()
{
    centerXCoordinateInPercent = 50;
    centerYCoordinateInPercent = 50;


    arrows = new WatchArrow[1];
    arrowsCount = 0;
    WatchArrow * watchArrow = new WatchArrow();
    arrows[arrowsCount++] = *watchArrow;
    watchArrow = new WatchArrow(3600, QColor(120, 120,0), 4, new QPoint[4]{QPoint(1,0),QPoint(-1,0),QPoint(-1,50),QPoint(1,50)});
    arrows[arrowsCount++] = *watchArrow;


    notchesTypesCount = 0;
    notches= new Notches[1];
    Notches * first_notches = new Notches () ;
    notches[notchesTypesCount++] = *first_notches;
    Notches * second_notches = new Notches (24, QColor(255, 0, 132), 40,0,50,0) ;
    notches[notchesTypesCount++] = *second_notches;
}

void WatchDial::draw(QPainter *p, long time)
{
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

