#include "watchdial.h"

WatchDial::WatchDial()
{

}

void WatchDial::draw(QPainter *p, long time)
{
    for(int i = 0; i < arrowsCount; i++){
        float angle = time * arrows[i].getSpeed();
        //TODO: проверить на >= 360
        arrows[i].draw(p, angle);
    }
}
