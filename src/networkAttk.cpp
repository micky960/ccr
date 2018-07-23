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

        if(tokens[1].find("OUTPUT") != std::string::npos)
            _parsePin(line);
        else _parseCell(line); 
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

    CELL* c;

    c->name = name;
    boost::algorithm::trim(tokens[1]);
    c->type = tokens[1];
   
    //std::cout << c->name << " " << c->type << std::endl;

    //delims = "|";
    //boost::algorithm::iter_split(tokens, tokens[2], boost::first_finder(delims));
}

void NETWORKFLOW::_parsePin(std::string line){

}
