#include<iostream>
#include<vector>
#include <boost/algorithm/string.hpp>

//#include "cell.h"
typedef struct{

    std::string srcName, srcPin;

}pPP;

class PIN{

    public:
        std::string name;
        bool io;
        pPP src;
        //CELL* src;
        PIN(std::string line);
        bool isInput(){return io;}
        void setSrc(std::string srcName, std::string srcPin);
};
