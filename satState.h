#include <string>

#include "formula.h"
#include "DPLLSolver.h"
#include "cnfFileFormatter.h"
#include "resultFormatter.h"

#ifndef SATSATE_H
#define SATSATE_H
class Sat;

enum Input{
    READFile=1,SHOWFORMULA=2,SOLVE=3,VALIDATE=4,STORE=5
};

class SatState
{
private:
public:
    SatState(){};
    ~SatState(){};
    virtual SatState* handleInput(Input input)=0;
    virtual void update(Sat&sat)=0;
};


class Sat
{
private:
public:
    Sat();
    ~Sat() {if(formula.literal_polarity!=nullptr)delete formula.literal_polarity;}

    Formula formula;
    SolveResult result;
    std::string filename;
    SatState *state_;
    virtual void handleInput(Input input);
    virtual void update(){
        state_->update(*this);
    }
};



class ReadFileState:public SatState
{
private:
    CnfFileFormatter formatter;
public:
    ReadFileState() {}
    ~ReadFileState() {}
    virtual SatState* handleInput(Input input);
    virtual void update(Sat&sat);
};

class ShowFormulaState:public SatState
{
private:
public:
    ShowFormulaState() {}
    ~ShowFormulaState() {}
    virtual SatState* handleInput(Input input);
    virtual void update(Sat&sat);
};

class SolveState:public SatState
{
private:
    DPLLSolver solver;
    SolveResult solve_process(Formula&formula);
public:
    SolveState() {}
    ~SolveState() {}
    virtual SatState* handleInput(Input input);
    virtual void update(Sat&sat);
};

class ValidateState:public SatState
{
private:
    ResultFormatter formatter;
public:
    ValidateState() {}
    ~ValidateState() {}
    virtual SatState* handleInput(Input input);
    virtual void update(Sat&sat);
};

class StoreState:public SatState{
private:
    ResultFormatter exporter;
public:
    StoreState(){}
    ~StoreState(){}
    virtual SatState*handleInput(Input input);
    virtual void update(Sat&sat);
};

class InitState:public SatState
{
public:
    virtual SatState*handleInput(Input input){
        if(input==READFile)return new ReadFileState();
        return nullptr;
    }
    virtual void update(Sat&sat){}
};
void show_processing(bool &running,std::vector<std::string>&words);
#endif