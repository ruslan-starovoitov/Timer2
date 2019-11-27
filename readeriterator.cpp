#include "readeriterator.h"
#include <string>
#include <sstream>
#include <vector>

ReaderIterator::ReaderIterator()
{
    infile = new std::ifstream("D:\\data.txt");
    MoveNext();
}

ReaderIterator::~ReaderIterator()
{
    if(infile != nullptr)
    {
        infile->close();
        delete infile;
    }
}

void ReaderIterator::MoveNext()
{
    try {
        if (infile->is_open())
        {
            std::string line;
            if (getline(*infile, line))
            {
                std::cout << line << std::endl;
                std::stringstream ss(line);
                std::string item;
                std::vector<std::string> words;
                while (std::getline(ss, item, ' ')) {
                  words.push_back(item);
                }

                if(words.size() != 5)
                {
                    currentPlaneInfo = nullptr;
                    throw "words count != 5";
                }

                currentPlaneInfo = new PlaneInfo();
                currentPlaneInfo->timeMs = std::stoll(words[0]);
                currentPlaneInfo->radius = std::stod(words[1]);
                currentPlaneInfo->height = std::stoi(words[2]);
                currentPlaneInfo->velocity = std::stoi(words[3]);
                currentPlaneInfo->index = std::stoi(words[4]);
            }
            else {
                currentPlaneInfo = nullptr;
            }
        }
        else {
            currentPlaneInfo = nullptr;
        }
    } catch (std::string msg) {
        std::cout << msg;
    }
}

bool ReaderIterator::HasValue()
{
    return currentPlaneInfo!=nullptr;
}

PlaneInfo *ReaderIterator::GetCurrent()
{
    return currentPlaneInfo;
}

