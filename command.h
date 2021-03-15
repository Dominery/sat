#include "DPLLSolver.h"
#include "formula.h"
#ifndef COMAND_H
#define COMAND_H
class Command
{
    public:
    virtual int execute(Formula&)=0;
};


//SAT process command

class ParseFileCommand:public Command{
    public:
    ParseFileCommand(){};
    virtual int execute(Formula&);
};

class ShowFormulaCommand:public Command{

    public:
    ShowFormulaCommand(){};
    virtual int execute(Formula&);
};

class SolveFormulaCommand:public Command{
    public:
    SolveFormulaCommand(){};
    virtual int execute(Formula&);
    private:
    SolveResult solve_process(Formula&);
};

class ExitCommand:public Command{
    public:
    virtual int execute(Formula&);
};
#endif