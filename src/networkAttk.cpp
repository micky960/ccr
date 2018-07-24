#include<boost/algorithm/string.hpp>  
#include<sstream>

#include "networkAttk.h"

NETWORKFLOW::NETWORKFLOW(std::ifstream& networkFile){

    std::string line;

    getline(networkFile, line);
    getline(networkFile, line);

    while(getline(networkFile, line)){
        std::vector<std::string> tokens;
        std::string delims = "+++";
        boost::algorithm::iter_split(tokens, line, boost::first_finder(delims));

        if(tokens[1].find("OUTPUT") != std::string::npos){
            _parsePin(line);
        }
        else if(tokens[1].find("INPUT") == std::string::npos){
            //std::cout << "line: " << line << std::endl;
            _parseCell(line); 
        }
        else{}//reserved for parsing PI
    }

}

void NETWORKFLOW::printCells(){

    for(const auto [name, c]: cellList){
        c->printCell();
        std::cout << std::endl;
    }

}

void NETWORKFLOW::printPins(){

    for(const auto [name, p]: pinList){

        if(!p->isInput()){
            p->printPin();
        }
    }
}

void NETWORKFLOW::_parseCell(std::string line){

    std::vector<std::string> tokens;
    std::string delims = "+++";
    boost::algorithm::iter_split(tokens, line, boost::first_finder(delims));

    std::stringstream ss(tokens[0]);
    std::string name;
    ss>>name;
    ss>>name;

    CELL* c = new CELL();

    c->name = name;
    boost::algorithm::trim(tokens[1]);
    c->type = tokens[1];
   
    delims = "|";
    boost::algorithm::iter_split(tokens, line, boost::first_finder(delims));

    for(int i=1; i<tokens.size()-1; i++){
        //std::cout << "token: " << tokens[i] << std::endl;
        _parseCellPin(tokens[i], c);
    }

    cellList[c->name] = c;
}

void NETWORKFLOW::_parsePin(std::string line){

    //std::cout << line << std::endl;
    std::vector<std::string> tokens;
    std::string delims = "+++";
    boost::algorithm::iter_split(tokens, line, boost::first_finder(delims));

    std::stringstream ss(tokens[0]);
    std::string name;
    ss>>name;
    ss>>name;
   
    PIN* p = new PIN();
    
    p->name = name;

    boost::algorithm::trim(tokens[1]);
   
    delims = "|";
    boost::algorithm::iter_split(tokens, line, boost::first_finder(delims));

    for(int i=1; i<tokens.size()-1; i++){

            std::vector<std::string> tokens2;
            std::string delims = ":";
            boost::algorithm::iter_split(tokens2, tokens[i], boost::first_finder(delims));

            std::string sinkPinName, srcInstName, srcPinName, temp;

            std::stringstream ss(tokens2[2]);
            ss>>srcInstName;
            boost::algorithm::trim(srcInstName);
            ss>>srcPinName;
            ss>>srcPinName;
            boost::algorithm::trim(srcPinName);

            bool isBEOL;
            if(tokens[1].find("BEOL") != std::string::npos)
                isBEOL = true;
            else isBEOL = false;

            if(srcPinName.find("Primary") != std::string::npos)
                p->setSrc("PIN", srcInstName, isBEOL);
            else
                p->setSrc(srcInstName, srcPinName, isBEOL);
        }

        pinList[p->name] = p;

}

void NETWORKFLOW::_parseCellPin(std::string tok, CELL* c){

    //std::cout << tok << std::endl;
    std::vector<std::string> tokens;
    std::string delims = ":";
    boost::algorithm::iter_split(tokens, tok, boost::first_finder(delims));
    //std::cout << tokens.size() << std::endl;

    std::string sinkPinName, srcInstName, srcPinName, temp;
    boost::algorithm::trim(tokens[0]);
    sinkPinName = tokens[0];

    //std::cout << c->name << "Sink pin name " << sinkPinName << std::endl;
    std::stringstream ss(tokens[2]);
    //ss>>temp;
    //std::cout << temp << std::endl;
    ss>>srcInstName;
    boost::algorithm::trim(srcInstName);
    ss>>srcPinName;
    ss>>srcPinName;
    boost::algorithm::trim(srcPinName);

    //std::cout << "sink pin: " << sinkPinName << "src inst:" << srcInstName << "src inst pin:" << srcPinName << std::endl;

    bool isBEOL;
    if(tokens[1].find("BEOL") != std::string::npos)
        isBEOL = true;
    else isBEOL = false;

    if(srcPinName.find("Primary") != std::string::npos)
        c->setSrc(sinkPinName, "PIN", srcInstName, isBEOL);
    else
        c->setSrc(sinkPinName, srcInstName, srcPinName, isBEOL);
}

