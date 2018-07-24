#ifndef CELL_H
#define CELL_H

#include<iostream>
#include<vector>
#include<unordered_map>

typedef struct pinPair{
    std::string srcName, srcPinName, sinkName, sinkPinName;
    bool isSourcePI = false, isBEOL = false;
}cPP;

class CELL: public pinPair{

    public:
        std::string name, type;
        std::unordered_map<std::string, cPP> ipList;
        CELL(std::string line);
        CELL();
        void setSrc(std::string sinkPinName, std::string srcName, std::string srcPinName, bool isBEOL);
        void printCell();
        std::unordered_map<std::string, cPP> getIpList(){return ipList;}
};

#endif
