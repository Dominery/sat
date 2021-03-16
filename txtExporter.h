#include <fstream>
#include <string>
#include "DPLLSolver.h"
#ifndef TXTEXPORTER_H
#define TXTEXPORTER_H

class TxtExporter
{
private:
    std::string extension;
public:
    TxtExporter(std::string ext):extension(ext){};
    ~TxtExporter(){};
    void output(std::string,SolveResult&);
};
#endif