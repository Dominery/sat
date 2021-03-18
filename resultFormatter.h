#include <fstream>
#include <string>
#include <iostream>
#include "DPLLSolver.h"
#ifndef TXTEXPORTER_H
#define TXTEXPORTER_H

class ResultFormatter{
    public:
    // transfer the data of result as ouput stream
    void format(SolveResult&,std::ostream&);
    // parse file which contains result of formula
    // to object of SolveResult
    SolveResult parse(std::ifstream&);
};
#endif