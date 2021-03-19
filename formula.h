#include<vector>
#include <list>
#ifndef FORMULA_H
#define FORMULA_H
typedef std::vector<int> clause;

// encode positive literals as even, negative literals as odd
// if the literal is true, the encoded number of its positive  can be divide by 2 exactly
// while the negative can't 
#define ENCODE(x) (x>0?(x-1)*2:-2*x-1) 
#define DECODE(x) (x%2?(x+1)/2*(-1):x/2+1)
struct FormulaInfo
{
    // the num of remained clauses 
    int clauses_num;
    // the num of literals in every clause
    std::vector<int> clause_literals_num;
    // store the num of every literal
    std::vector<int> literal_frequency;
    // store the literal which assigned
    int literal_choice;

    FormulaInfo():clauses_num(0){}
    FormulaInfo(int cl_num,std::vector<int>cl_lit_num,std::vector<int>lit_fre):
    clauses_num(cl_num),clause_literals_num(cl_lit_num),literal_frequency(lit_fre){}
};
struct Formula{
    // a vector that stores the value assigned to each variable, where
    // -1 unassigned
    // 0 true
    // 1 false
    std::vector<int> literals;
    FormulaInfo info;
    // store index of clauses that the same literal in
    std::vector<std::list<int>> literals_position;
    int *literal_polarity=nullptr;
    // contain clauses
    std::vector<clause> clauses;
    Formula(){
        literals.clear();
        clauses.clear();
    };
    Formula(int lit_num){
        literals = std::vector<int>(lit_num,-1);
        info.literal_frequency = std::vector<int>(lit_num,0);
        literals_position = std::vector<std::list<int>>(lit_num);
        literal_polarity = new int[lit_num];
        for(int i=0;i<lit_num;++i){
            literal_polarity[i]=0;
        }
    };
    bool not_init(){
        return info.clauses_num==0;
    };
    void  add_clause(std::vector<int> literals){
    for(auto &lit:literals){
        lit = ENCODE(lit);
        info.literal_frequency[lit/2]++;
        lit%2?literal_polarity[lit/2]--:literal_polarity[lit/2]++;
        literals_position[lit/2].push_back(info.clauses_num);
    }
    info.clause_literals_num.push_back(literals.size());
    info.clauses_num++;
    clauses.push_back(std::move(literals));
}
};
#endif