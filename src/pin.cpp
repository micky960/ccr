#include<sstream>
#include<boost/algorithm/string.hpp>

#include "pin.h"

PIN::PIN(std::string line){
    
    std::vector<std::string> tokens;
    boost::split(tokens, line, boost::is_any_of(" "));
    boost::algorithm::trim(tokens[1]);
    name = tokens[1];

    std::string dir = tokens[7];
    boost::algorithm::trim(dir);
    io = (dir.compare("INPUT"))? false : true;

}

PIN::PIN(){
    io = false;
}

void PIN::setSrc(std::string srcName, std::string srcPin, bool isBEOL){

    src.srcName = srcName;
    src.srcPin = srcPin;
    src.isBEOL = isBEOL;

}

void PIN::printPin(){
    std::cout << "Pin: " << name << "-->" << std::endl;
    std::cout << src.srcName << ": " << src.srcPin << std::endl; 
    std::cout << std::endl;
}
