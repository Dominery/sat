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
    int *literal_polarity=nullptr;
    std::vector<clause> clauses;
    Formula(std::vector<clause> &cl,std::vector<int>&lit_f,std::vector<int>&lit):literals(lit),clauses(cl),literal_frequency(lit_f){}
    Formula(){
        literals.clear();
        literal_frequency.clear();
        clauses.clear();
    };
    Formula(int num){
        literals = std::vector<int>(num,-1);
        literal_frequency = std::vector<int>(num,0);
        literal_polarity = new int[num];
        for(int i=0;i<num;++i){
            literal_polarity[i]=0;
        }
    };
    Formula(const Formula &formula){
        literals = formula.literals;
        clauses = formula.clauses;
        literal_frequency = formula.literal_frequency;
        literal_polarity = formula.literal_polarity;
    };
    bool not_init(){
        return clauses.empty();
    };
    void  add_clause(std::vector<int> literals){
    for(auto &lit:literals){
        lit = ENCODE(lit);
        literal_frequency[lit/2]++;
        lit%2?literal_polarity[lit/2]--:literal_polarity[lit/2]++;
    }
    clauses.push_back(literals);
}
};
#endif