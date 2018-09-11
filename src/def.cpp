#include<string.h>
#include <boost/algorithm/string.hpp>

#include "def.h"

DEF::DEF(std::ifstream& def){

   _parseComponents(def); 
        //std::cout << "Cell parse passed" << std::endl;
   _parsePins(def); 
        //std::cout << "Pin parse passed" << std::endl;
   _parseNets(def); 
        //std::cout << "Net parse passed" << std::endl;

}

void DEF::printCells(){

    for(const auto [name, c]: cellList){
        c->printCell();
        std::cout << std::endl;
    }

}

void DEF::printPins(){

    for(const auto [name, p]: pinList){

        if(!p->isInput()){
            std::cout << "Pin: " << p->name << "-->" << std::endl;
            std::cout << p->src.srcName << ": " << p->src.srcPin << std::endl; 
            std::cout << std::endl;
        }
    }


}

void DEF::_parseComponents(std::ifstream& def){
    std::string line;
    getline(def, line);
    while(line.find("COMPONENTS")==std::string::npos)
        getline(def, line);


    std::vector<std::string> tokens;
    while(line.find("END COMPONENTS")==std::string::npos){//parse all complist

        getline(def, line);
        if(line.find(";")!=std::string::npos||line.find("END COMPONENTS")!=std::string::npos)
            continue;
        CELL* cell = new CELL(line);
        //std::cout << cell->name << std::endl;
        cellList[cell->name] = cell;
    }

}

void DEF::_parsePins(std::ifstream& def){

    std::string line, name, dir;

    getline(def, line);
    getline(def, line);
    getline(def, line);


    while(line.find("END PINS")==std::string::npos){
        PIN* pin = new PIN(line);
        pinList[pin->name] = pin;

        //std::cout << pin->name << "-->" << pin->isInput() << std::endl;
        
        getline(def, line);
        getline(def, line);
        getline(def, line);

    }
    //std::cout << line << std::endl;

}

void DEF::_parseNets(std::ifstream& def){
   
    std::string line;

    do{
        getline(def, line);
    }while(line.find("END SPECIALNETS")==std::string::npos);

    getline(def, line);
    getline(def, line);
    getline(def, line);

    //std::cout << line << std::endl;
    while(line.find("END NETS")==std::string::npos){

        std::string head = ""; 
        boost::trim(line);
        while(boost::starts_with(line, "-") || boost::starts_with(line, "(")){
            head += line+"\n";
            getline(def, line);
            boost::algorithm::trim(line);
        }
        //std::cout << head << std::endl;

        NET* net = new NET(head, cellList, pinList);

        while(line.find(";")==std::string::npos)
            getline(def, line);

        getline(def, line);
        //std::cout << line << std::endl;
    } 
    
}
