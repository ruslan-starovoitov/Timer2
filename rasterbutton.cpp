#include "rasterbutton.h"
using namespace std;

RasterButton::RasterButton(QColor *color, const char *text, int x, int y, int width, int height)
{
    buttonColor = color;
    buttonText = QString(text);
    rectangle = QRect(x, y, width, height);
}

void RasterButton::draw(QPainter *p)
{
    //QRect boundingRect;

    p->setPen(Qt::NoPen);
    p->setBrush(*buttonColor);
    p->drawRect(rectangle);
    p->setBrush(QColor(30,100,50));
    p->drawText(rectangle, 0, buttonText);
}

void RasterButton::mouseMoveEvent(QMouseEvent *event)
{

}

void RasterButton::mousePressEvent(QMouseEvent *event)
{

}
