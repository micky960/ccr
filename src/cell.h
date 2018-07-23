#include<iostream>
#include<vector>
#include<unordered_map>

typedef struct pinPair{
    std::string srcName, srcPinName, sinkName, sinkPinName;
    bool isSourcePI = false;
}cPP;

class CELL: public pinPair{

    public:
        std::string name, type;
        std::unordered_map<std::string, cPP> ipList;
        CELL(std::string line);
        void setSrc(std::string sinkPinName, std::string srcName, std::string srcPinName);
};
