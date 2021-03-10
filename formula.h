#include<vector>
#ifndef FORMULA_H
#define FORMULA_H
typedef std::vector<int> clause;

struct Formula{
    // a vector that stores the value assigned to each variable, where
    // -1 unassigned
    // 0 true
    // 1 false
    std::vector<int> literals;
    std::vector<int> literal_frequency;
    std::vector<clause> clauses;
    Formula(std::vector<clause> &cl,std::vector<int>&lit_f,std::vector<int>&lit):literals(lit),clauses(cl),literal_frequency(lit_f){}
    Formula(){};
    Formula(const Formula &formula){
        literals = formula.literals;
        clauses = formula.clauses;
        literal_frequency = formula.literal_frequency;
    }
};

#endif