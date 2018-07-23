#include<sstream>
#include <boost/algorithm/string.hpp>

#include "net.h"

NET::NET(std::string net, std::unordered_map<std::string, CELL*> glbCellList, std::unordered_map<std::string, PIN*> glbPinList){

    std::string inst, cell, pin, type;
    std::stringstream ss(net);
    getline(ss, inst, '\n');
    std::stringstream ssName(inst);
    ssName >> name;
    ssName >> name;//save net name
    boost::algorithm::trim(name);
    //std::cout << name << std::endl;

    while(getline(ss, inst, '\n')){
        //std::cout << inst << std::endl;
        std::vector<std::string> tokens;
        boost::split(tokens, inst, boost::is_any_of("("));

        for(unsigned i=1; i<tokens.size(); i++){//parse cell/pin names; 1st token is always empty
            std::stringstream ss1;
            ss1<<tokens[i];
            ss1>>type;
            ss1<<tokens[i];
            ss1>>pin;

            if(type.find("PIN") != std::string::npos){
                nPP p;
                p.pin = glbPinList[pin]->name;
                if(glbPinList[pin]->isInput()){
                    srcIsPin = true;
                    src.instName = "PIN";
                    src.pinName = p.pin;
                    pinList.push_back(p);
                } 
            }

            else{
                nCP c;
                c.cell = glbCellList[type]->name;
                c.pin = pin;
                if(pin.find("Z") != std::string::npos){//add rest CO, S(HA/FA), ZN, Q, QN
                    srcIsCell = true;
                    src.instName = c.cell;
                    src.pinName = pin;
                    cellList.push_back(c);
                } 
            }
        }


    }

    _parseCells(glbCellList);    
    //_parsePins(glbPinList);    

}

void   NET::_parseCells(std::unordered_map<std::string, CELL*> glbCellList){

    for(const auto c : cellList) {
        CELL* cur = glbCellList[c.cell];
        std::cout << "srcName: " << src.instName << ", srcPin: " << src.pinName << ", sinkName: " << c.cell << ", sinkPinName:" << c.pin << std::endl;
        cur->setSrc(c.pin, src.instName, src.pinName);
    }   

}

void   NET::_parsePins(std::unordered_map<std::string, PIN*> glbPinList){
    for(const auto p : pinList) {
        PIN* cur = glbPinList[p.pin];
        if(!cur->isInput()){
            cur->setSrc(src.instName, src.pinName);
        }
    }   

}