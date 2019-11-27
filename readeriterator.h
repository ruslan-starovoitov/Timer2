#ifndef READERITERATOR_H
#define READERITERATOR_H

#include "planeinfo.h"
#include "string"
#include <iostream>
#include <fstream>



class ReaderIterator
{
public:
    ReaderIterator();
    ~ReaderIterator();
    void MoveNext();
    bool HasValue();
    PlaneInfo* GetCurrent();
private:
    PlaneInfo* currentPlaneInfo;
    std::ifstream* infile;
};

#endif // READERITERATOR_H
