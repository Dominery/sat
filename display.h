#include "formula.h"
#include "DPLLSolver.h"
#ifndef DISPLAY_H
#define DISPLAY_H
class Display
{
private:
    void show_sat();
public:
    void run();
    Display(){};
    ~Display(){};
};
#endif