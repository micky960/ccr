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

int main(int argc, char* argv[]){

	assert(argc==2);

    std::ifstream def(argv[1]);

    if(def.fail()){
        std::cerr << "splitdef file not found"<<std::endl;
        exit(1);
    }

    DEF* def_parse = new DEF(def);

    //def_parse->printCells();

}
