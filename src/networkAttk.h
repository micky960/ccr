#include<iostream>
#include<string>
#include<unordered_map>
#include<fstream>

#include "cell.h"
#include "pin.h"

class NETWORKFLOW{

    public:
        std::unordered_map<std::string, CELL*> cellList;
        std::unordered_map<std::string, PIN*> pinList;
        NETWORKFLOW(std::ifstream& networkFile);
        std::unordered_map<std::string, CELL*> getCells(){return cellList;}
        std::unordered_map<std::string, PIN*> getPins(){return pinList;}
        void printCells();
        void printPins();
    private:
        void _parseCell(std::string line);
        void _parsePin(std::string line);
        void _parseCellPin(std::string tok, CELL* c);
};
