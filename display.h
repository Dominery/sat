#include "formula.h"
#include "DPLLSolver.h"
#ifndef DISPLAY_H
#define DISPLAY_H
class Display
{
private:
    void show_sat();
public:
    void run_sat_menu();
    Display(){};
    ~Display(){};
};
#endif