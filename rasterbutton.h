#ifndef RASTERBUTTON_H
#define RASTERBUTTON_H
#include <QtGui>
using namespace std;

class RasterButton
{
public:
    RasterButton(QColor *color, const char *text, int x, int y, int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void draw(QPainter *p);

public:
private:
    QColor *buttonColor;
    QString buttonText;
    QRect rectangle;
};

#endif // RASTERBUTTON_H
