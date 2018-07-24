#ifndef PIN_H
#define PIN_H

#include<iostream>
#include<vector>
#include <boost/algorithm/string.hpp>

//#include "cell.h"
typedef struct{

    std::string srcName, srcPin;
    bool isBEOL = false;

}pPP;

class PIN{

    public:
        std::string name;
        bool io;
        pPP src;
        //CELL* src;
        PIN(std::string line);
        PIN();
        bool isInput(){return io;}
        void setSrc(std::string srcName, std::string srcPin, bool isBEOL);
        void printPin();
};

#endif
