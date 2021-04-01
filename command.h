#include <string>
#include <vector>
#include "DPLLSolver.h"
#include "formula.h"
#include "resultFormatter.h"
#include "cnfFileFormatter.h"
#include "sudoku.h"
#include "DPLLSolver.h"
#ifndef COMAND_H
#define COMAND_H


struct CommandInfo{
    Formula formula;
    std::string filename;
    SolveResult result;
    ~CommandInfo(){
        if(formula.literal_polarity!=nullptr)delete formula.literal_polarity;
    };
};
class Command
{
    public:
    virtual int execute(CommandInfo&)=0;
};


class ExitCommand:public Command{
    public:
    virtual int execute(CommandInfo&);
};


class GenerateSudoCommand:public Command{
    private:
    PuzzleGenerator generator;
    void play_sudo(Sudoku&sudo,Sudoku&puzzle);
    public:
    virtual int execute(CommandInfo&);
};


void show_processing(bool &running,std::vector<std::string>&words);
#endif