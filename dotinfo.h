#ifndef DOTINFO_H
#define DOTINFO_H


class DotInfo
{
public:
    DotInfo(int fadingT = 600);
    ~DotInfo();
    double x;
    double y;
    int height;
    int velocity;
    int index;
    int fadingTime;
    int timeToFade;
};

#endif // DOTINFO_H
