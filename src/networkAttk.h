#include<iostream>
#include<string>
#include<unordered_map>
#include<fstream>

#include "cell.h"

class NETWORKFLOW{

    public:
        std::unordered_map<std::string, CELL*> cellList;
        NETWORKFLOW(std::ifstream& networkFile);
        void _parseCell(std::string line);
        void _parsePin(std::string line);
};
