#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "DPLLSolver.h"
#ifndef TXTEXPORTER_H
#define TXTEXPORTER_H

class ResultFormatter{
    public:
    // transfer the data of result as ouput stream
    void format(SolveResult&,std::ostream&);
    // transfer solveResult to vector contained 0 or 1
    std::vector<int> format(SolveResult&);
};
#endif