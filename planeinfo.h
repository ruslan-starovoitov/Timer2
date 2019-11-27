#ifndef PLANEINFO_H
#define PLANEINFO_H


class PlaneInfo
{
public:
    PlaneInfo();
    ~PlaneInfo();
    long long timeMs;
    double radius;
    int height;
    int velocity;
    int index;
};

#endif // PLANEINFO_H
