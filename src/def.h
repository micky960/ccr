#include<iostream>
#include<fstream>
#include<unordered_map>

#include "net.h"
#include "cell.h"

class DEF{

    public:
        std::unordered_map<std::string, CELL*> cellList;
        std::unordered_map<std::string, PIN*> pinList;
        std::unordered_map<std::string, NET*> netList;
        DEF(std::ifstream& def);
        std::unordered_map<std::string, CELL*> getCells(){return cellList;}
        void printCells();
        void printPins();

    private:
        void _parseComponents(std::ifstream& def);
        void _parsePins(std::ifstream& def);
        void _parseNets(std::ifstream& def);
};
