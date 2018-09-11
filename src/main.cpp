#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<stdlib.h>
#include<cassert>
#include<cmath>
#include<numeric>
#include <list>
#include <omp.h>
#include <boost/algorithm/string.hpp>

#include "def.h"
#include "networkAttk.h"

int tot = 0, corr = 0;

void ccrCells(std::unordered_map<std::string, CELL*> defCells, std::unordered_map<std::string, CELL*> netwrkflwCells);
void ccrPins(std::unordered_map<std::string, PIN*> defPins, std::unordered_map<std::string, PIN*> netwrkflwPINs);
int main(int argc, char* argv[]){

	assert(argc==3);

    std::ifstream def(argv[1]);
    std::ifstream networkflow(argv[2]);

    if(def.fail()){
        std::cerr << "splitdef file not found"<<std::endl;
        exit(1);
    }
    if(networkflow.fail()){
        std::cerr << "networkflow file not found"<<std::endl;
        exit(1);
    }

    DEF* def_parse = new DEF(def);
        std::cout << "Def parsed" <<std::endl;
    NETWORKFLOW* netwrkflw_parse = new NETWORKFLOW(networkflow);
        std::cerr << "Networkflow parsed"<<std::endl;

    std::unordered_map<std::string, CELL*> defCells, netwrkflwCells;
    std::unordered_map<std::string, PIN*> defPins, netwrkflwPins;

    defCells = def_parse->getCells();
    netwrkflwCells = netwrkflw_parse->getCells();

    defPins = def_parse->getPins();
    netwrkflwPins = netwrkflw_parse->getPins();

    ccrCells(defCells, netwrkflwCells);
    ccrPins(defPins, netwrkflwPins);
    //def_parse->printCells();
    //def_parse->printPins();


    //netwrkflw_parse->printCells();
    //netwrkflw_parse->printPins();
    std::cout << "total: "<<tot<<"\tcorrect: "<<corr<< "\t\% correct connections: " << (double)corr/tot*100 << std::endl;
}

//void ccrCells(std::unordered_map<std::string, CELL*> defCells, std::unordered_map<std::string, CELL*> netwrkflwCells){
//
//    int cellTot = 0, cellCorr = 0;
//    for(const auto [name1, c1]: netwrkflwCells){
//        std::unordered_map<std::string, cPP> netwrkflwIpList = c1->getIpList(); 
//        for(const auto [name2, p1]: netwrkflwIpList){
//            if(p1.isBEOL){
//                tot++; 
//                cellTot++;
//                CELL* c2 = defCells[c1->name];
//                std::unordered_map<std::string, cPP> defIpList = c2->getIpList();
//                cPP p2 = defIpList[p1.sinkPinName];
//                if(p2.srcName == p1.srcName && p2.srcPinName == p1.srcPinName){
//                    corr++;
//                    cellCorr++;
//                }
//            }
//        }
//    }
//
//    std::cout << "Cell-------->total: "<<cellTot<<"\tcorrect: "<<cellCorr<< "\t\% correct connections: " << (double)cellCorr/cellTot*100 << std::endl;
//
//}

void ccrCells(std::unordered_map<std::string, CELL*> defCells, std::unordered_map<std::string, CELL*> netwrkflwCells){

    int cellTot = 0, cellCorr = 0, keyTot = 0, keyCorr = 0;
    for(const auto [name1, c1]: netwrkflwCells){
        std::unordered_map<std::string, cPP> netwrkflwIpList = c1->getIpList(); 
        for(const auto [name2, p1]: netwrkflwIpList){
            if(p1.isBEOL){
                tot++; 
                cellTot++;
                CELL* c2 = defCells[c1->name];
                std::unordered_map<std::string, cPP> defIpList = c2->getIpList();
                cPP p2 = defIpList[p1.sinkPinName];
                if(p2.isKey){
                    keyTot++;
                    std::cout << "Driver:" << p2.srcName << ",\t Sink:" << c2->name << std::endl;
                    if(p1.srcName.find("logic_0") != std::string::npos && p2.srcName.find("logic_0") != std::string::npos || p1.srcName.find("logic_1") != std::string::npos && p2.srcName.find("logic_1") != std::string::npos ){
                        std::cout << "Correct! Driver:" << p1.srcName << ",\t Sink:" << c1->name << std::endl;
                        keyCorr++;
                        //this is to consider physical ccr for regular nets only
                        tot--;//tot should not increase if key net
                        //corr++;
                        //cellCorr++;
                    }
                    else{
                        std::cout << "Wrong! Driver: " << p1.srcName << ",\t Sink:" << name1 << std::endl;
                    }
                }
                else if(p2.srcName == p1.srcName && p2.srcPinName == p1.srcPinName){
                    corr++;
                    cellCorr++;
                }
            }
        }
    }

    std::cout << "Key-------->total: "<<keyTot<<"\tcorrect: "<<keyCorr<< "\t\% correct connections: " << (double)keyCorr/keyTot*100 << std::endl;
    std::cout << "Cell-------->total: "<<cellTot<<"\tcorrect: "<<cellCorr<< "\t\% correct connections: " << (double)cellCorr/cellTot*100 << std::endl;

}

void ccrPins(std::unordered_map<std::string, PIN*> defPins, std::unordered_map<std::string, PIN*> netwrkflwPins){

    int pinTot = 0, pinCorr = 0;
    for(const auto [name1, p1]: netwrkflwPins){
        if(p1->src.isBEOL){
            tot++;
            pinTot++;
            PIN* p2 = defPins[p1->name];
            if(p2->src.srcName == p1->src.srcName && p2->src.srcPin == p1->src.srcPin){
                corr++;
                pinCorr++;
            }
        }
    }
    std::cout << "Pin-------->total: "<<pinTot<<"\tcorrect: "<<pinCorr<< "\t\% correct connections: " << (double)pinCorr/pinTot*100 << std::endl;

}
