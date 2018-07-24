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

    //def_parse->printCells();
    //def_parse->printPins();

    NETWORKFLOW* netwrkflw_parse = new NETWORKFLOW(networkflow);

    //netwrkflw_parse->printCells();
}
