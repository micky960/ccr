#ifndef NET_H
#define NET_H

#include<iostream>
#include<string>
#include <boost/algorithm/string.hpp>

#include "cell.h"
#include "pin.h"

typedef struct{
    std::string instName, pinName;
}nSP;

typedef struct{
    std::string cell, pin;
}nCP;

typedef struct{
    std::string pin;
}nPP;

class NET{
    public:
        std::string name;
        nSP src;
        bool srcIsPin, srcIsCell;
        std::vector<nCP> cellList;
        std::vector<nPP> pinList;
        NET(std::string net, std::unordered_map<std::string, CELL*> cellList, std::unordered_map<std::string, PIN*> pinList);
        bool getSrcIsPin(){return srcIsPin;}
        bool getSrcIsCell(){return srcIsCell;}
        std::vector<nCP> getNetCells(){return cellList;}
        std::vector<nPP> getNetPins(){return pinList;}

    private:
        void _parseCells(std::unordered_map<std::string, CELL*> glbCellList);
        void _parsePins(std::unordered_map<std::string, PIN*> glbPinList);
};

#endif
