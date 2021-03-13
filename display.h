#include "formula.h"
#include "DPLLSolver.h"
#ifndef DISPLAY_H
#define DISPLAY_H
class Display
{
private:
    int get_command();
    void parse_file(Formula&);
    void show_formula(Formula&);
    SolveResult process_formula(Formula&);
    void show_result(const SolveResult&);
    void show_sat();
public:
    void run();
    Display(){};
    ~Display(){};
};
#endif