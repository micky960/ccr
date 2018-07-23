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
                } 
                else    pinList.push_back(p);
            }

            else{
                nCP c;
                c.cell = glbCellList[type]->name;
                c.pin = pin;
                if(pin.find("ZN") != std::string::npos || pin.find("Z") != std::string::npos || pin.find("CO") != std::string::npos  || pin.find("QN") != std::string::npos  || pin.find("Q") != std::string::npos  || (pin.find("S") != std::string::npos && (glbCellList[type]->type.find("HA") != std::string::npos || glbCellList[type]->type.find("FA") != std::string::npos))){
                    srcIsCell = true;
                    src.instName = c.cell;
                    src.pinName = pin;
                } 
                else    cellList.push_back(c);
            }
        }


    }

    _parseCells(glbCellList);    
    _parsePins(glbPinList);    

}

void   NET::_parseCells(std::unordered_map<std::string, CELL*> glbCellList){

    for(const auto c : cellList) {
        CELL* cur = glbCellList[c.cell];
        //std::cout << "srcName: " << src.instName << ", srcPin: " << src.pinName << ", sinkName: " << c.cell << ", sinkPinName:" << c.pin << std::endl;
        cur->setSrc(c.pin, src.instName, src.pinName, false);
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
