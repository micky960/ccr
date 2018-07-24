#include<sstream>
#include<boost/algorithm/string.hpp>

#include "cell.h"

CELL::CELL(std::string line){
    
    std::vector<std::string> tokens;
    boost::split(tokens, line, boost::is_any_of("-"));
    std::stringstream ss;
    ss<<tokens[1];
    ss>>name;//get name of comp
    ss<<tokens[1];
    ss>>type;//type of comp
}

CELL::CELL(){

}

void CELL::setSrc(std::string sinkPinName, std::string srcName, std::string srcPinName, bool isBEOL){

    cPP cur;
    cur.sinkName = name;
    cur.sinkPinName = sinkPinName;
    cur.srcName = srcName;
    cur.srcPinName = srcPinName;
    cur.isBEOL = isBEOL;

    if (ipList.find(cur.sinkPinName) == ipList.end()){
        ipList[cur.sinkPinName] = cur;
    }

    else{
        cPP err = ipList[cur.sinkPinName];
        std::cout << "Error: cell "<< name << "--> " << cur.sinkPinName << " pin already assigned to " << err.srcName << std::endl;
    }

}

void CELL::printCell(){

    std::cout << "Cell: " << name << "-->" << std::endl;

    for(const auto [pinName, p]: ipList)
        std::cout << p.sinkPinName << ": " << p.srcName << ": " << p.srcPinName << std::endl; 
}
