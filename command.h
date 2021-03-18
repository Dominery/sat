#include <string>
#include "DPLLSolver.h"
#include "formula.h"
#include "resultFormatter.h"
#include "cnfFileFormatter.h"
#include "sudoku.h"
#ifndef COMAND_H
#define COMAND_H


struct CommandInfo{
    Formula formula;
    std::string filename;
    ~CommandInfo(){
        if(formula.literal_polarity!=nullptr)delete formula.literal_polarity;
    };
};
class Command
{
    public:
    virtual int execute(CommandInfo&)=0;
};


//SAT process command

class ParseFileCommand:public Command{
    private:
    CnfFileFormatter file_formatter;
    public:
    ParseFileCommand(){};
    virtual int execute(CommandInfo&);
};

class ShowFormulaCommand:public Command{

    public:
    ShowFormulaCommand(){};
    virtual int execute(CommandInfo&);
};

class SolveFormulaCommand:public Command{
    public:
    SolveFormulaCommand(){};
    virtual int execute(CommandInfo&);
    static SolveResult solve_process(Formula&);
    private:
    ResultFormatter exporter;
    void store_result(std::string filename,SolveResult&result);
};

class ExitCommand:public Command{
    public:
    virtual int execute(CommandInfo&);
};


class GenerateSudoCommand:public Command{
    private:
    PuzzleGenerator generator;
    public:
    virtual int execute(CommandInfo&);
};

class SolveSudoCommand:public Command{
    public:
    virtual int execute(CommandInfo&);
};

#endif