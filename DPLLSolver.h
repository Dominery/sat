#ifndef DPLL_PROCESSOR_H
#define DPLL_PROCESSOR_H

enum Status{UNKNOWN=2,SATISFIABLE=1,UNSATISFIABLE=0,CONFLICT};

class DPLLSolver
{
private:
    Status preprocess();
    void decide_next_branch();
    Status deduce();
    int analyze_conflict();
    void backtrack(int level);
public:
    DPLLSolver();
    ~DPLLSolver();
    Status process();
};

DPLLSolver::DPLLSolver()
{
}

DPLLSolver::~DPLLSolver()
{
}


#endif