#include <stack>
#include "formula.h"
#ifndef DPLL_PROCESSOR_H
#define DPLL_PROCESSOR_H

enum Status{UNKNOWN=2,SATISFIABLE=1,UNSATISFIABLE=0,CONFLICT=3}; // before bug occurred because the CONFLICT is not assigned, so it equals to SATISFIABLE

class DPLLSolver
{
private:
    // stack contain all state of formula 
    // which can help for backtrack
    std::stack<Formula> fstack; 
    // store each choice
    std::stack<int> lstack;
    // current_node is the current formula 
    Formula current_node;

    int current_literal_choice;
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
    Status single_clause(Formula&);
    Status transform_clauses(Formula&,int literal);
public:
    DPLLSolver(Formula&);
    DPLLSolver(){};
    DPLLSolver(const DPLLSolver &solver){
        current_node = solver.current_node;
    }
    Formula get_current();
    ~DPLLSolver();
    Status process();
};


#endif