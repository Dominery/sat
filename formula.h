#include<vector>
#ifndef FORMULA_H
#define FORMULA_H
typedef std::vector<int> clause;

// encode positive literals as even, negative literals as odd
// if the literal is true, the encoded number of its positive  can be divide by 2 exactly
// while the negative can't 
#define ENCODE(x) (x>0?(x-1)*2:-2*x-1) 
#define DECODE(x) (x%2?(x+1)/2*(-1):x/2+1)

struct Formula{
    // a vector that stores the value assigned to each variable, where
    // -1 unassigned
    // 0 true
    // 1 false
    std::vector<int> literals;
    std::vector<int> literal_frequency;
    int *literal_polarity;
    std::vector<clause> clauses;
    Formula(std::vector<clause> &cl,std::vector<int>&lit_f,std::vector<int>&lit):literals(lit),clauses(cl),literal_frequency(lit_f){}
    Formula(){};
    Formula(const Formula &formula){
        literals = formula.literals;
        clauses = formula.clauses;
        literal_frequency = formula.literal_frequency;
        literal_polarity = formula.literal_polarity;
    };
    bool not_init(){
        return clauses.empty();
    };
};
#endif