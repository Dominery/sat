#include <stack>
#include <ctime>
#include <vector>
#include "formula.h"
#ifndef DPLL_PROCESSOR_H
#define DPLL_PROCESSOR_H

enum Status{UNKNOWN=2,SATISFIABLE=1,UNSATISFIABLE=0,CONFLICT=3}; // before bug occurred because the CONFLICT is not assigned, so it equals to SATISFIABLE
struct SolveResult{
    Status status=UNKNOWN;
    std::vector<int> results;
    double duration;
    SolveResult(){};
    SolveResult(Status s,std::vector<int>lit,double time):status(s),results(lit),duration(time){};
    SolveResult(const SolveResult &result){
        status = result.status;
        results = result.results;
        duration = result.duration;
    }
};



class DPLLSolver
{
private:
    // current formulainfo
    FormulaInfo info;
    // store another choice
    std::stack<FormulaInfo> info_stack;
    // store the result of every literals
    // a vector that stores the value assigned to each variable, where
    // -1 unassigned 0 true 1 false
    std::vector<int> literals;
    //store the first formula
    Formula formula;
    int clauses_num;

    // preprocess the formula and then push it to fstack
    Status preprocess();
    // change the current formula
    void decide_next_branch();
    // decrease the clauses in formula using rule
    Status deduce();
    // return where the fstack don't have conflicts
    int analyze_conflict();
    // pop the formula of fstack and change the current formula
    void backtrack(int level);
    // if clause only has a literal,make the literal true and transform clauses
    Status single_clause();
    Status transform_clauses(int literal);
    Status process();

    int choose_literal(int pos);
public:
    DPLLSolver(){};
    ~DPLLSolver(){};
    // get object of SolveResult of formula
    SolveResult get_result(Formula&formula);
};


#endif