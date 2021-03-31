#include<vector>
#include<algorithm>
#include<iostream>
#include "DPLLSolver.h"
using namespace std;

Status DPLLSolver::process(){
    Status status = preprocess();
    if(status != UNKNOWN)return status;
    while (1)
    {
        decide_next_branch(); 
        while (true)
        {
            status = deduce();
            if(status == CONFLICT){
                int level = analyze_conflict();
                if(level==0)return UNSATISFIABLE;
                else backtrack(level);
            }
            else if(status == SATISFIABLE)return SATISFIABLE;
            else break;
        }
        
    }
    
}

SolveResult DPLLSolver::get_result(Formula&formula){
    this->formula = formula;
    info = formula.info;
    clauses_num = info.clauses_num;
    literals = vector<int>(info.literal_frequency.size(),-1);
    clock_t start = clock();
    Status status = process();
    clock_t end = clock();
    vector<int> results;
    if(status==SATISFIABLE){
        for(int i=0;i<literals.size();i++){
            int value = literals[i]?-(i+1):i+1;
            results.push_back(value);
        }
    }
    info_stack = stack<FormulaInfo>();
    literals.clear();
    return SolveResult(status,results,end-start);
}

Status DPLLSolver::single_clause(){
    if(info.clauses_num==0)return SATISFIABLE;
    // single_found will be true until the formula doesn't have single clauses
    bool single_found = true;
    while (single_found)
    {
        single_found = false;
        for(int i=0;i<clauses_num;i++){
            if(info.clause_literals_num[i]==1){
                single_found = true;
                int literal = choose_literal(i);
                literals[literal/2] = literal%2;
                info.literal_frequency[literal/2]=-1; // mark the literal frequency
                info.clause_literals_num[i]--;
                info.clauses_num--;
                Status status = transform_clauses(literal/2);
                if (status==UNKNOWN)break;
                else return status;
            }
        }
    }
    return UNKNOWN;
    
}
int DPLLSolver::choose_literal(int pos){
    for(auto i:formula.clauses[pos]){
        if(info.literal_frequency[i/2]!=-1){
            return i;
        }
    }
    return 0;
}

Status DPLLSolver::transform_clauses(int literal){
    if(info.clauses_num==0)return SATISFIABLE;
    int value_of_literal = literals[literal]; // 0 true;1 false
    for(auto i:formula.literals_position[literal]){
        for(int lit=0;lit<formula.clauses[i].size()&&info.clause_literals_num[i];lit++){
            if(literal*2+value_of_literal==formula.clauses[i][lit]){
                info.clause_literals_num[i] =0;
                info.clauses_num--;
                if(info.clauses_num==0)return SATISFIABLE;
            }else if(literal == formula.clauses[i][lit]/2){
                info.clause_literals_num[i]--;
                if(info.clause_literals_num[i]==0){
                    return UNSATISFIABLE;
                }
            }
        }
    }
    return UNKNOWN;
}

Status DPLLSolver::preprocess(){
    Status status = single_clause();
    return status;
}

void DPLLSolver::decide_next_branch(){
    //find the literal with maximum frequency in current formula
    int i = distance(info.literal_frequency.begin(),
    max_element(info.literal_frequency.begin(),info.literal_frequency.end()));
    info.literal_frequency[i] = -1;

    info.literal_choice = i; 
    info_stack.push(info);

    int value = formula.literal_polarity[i]>0?0:1;
    literals[i] = (value+1)%2;
}
// deduce will judge the influence of the current branch
// return value:
//      SATISFIABLE if the formula are completed
//      CONFLICT if the clauses in formula have conflict
//      UNKNOWN can't deduce the result above 
Status DPLLSolver::deduce(){
    Status status = transform_clauses(info.literal_choice);
    if (status==UNSATISFIABLE)return CONFLICT;
    status = single_clause();
    if(status == UNSATISFIABLE)return CONFLICT;
    return status;
}

int DPLLSolver::analyze_conflict(){
    if(info_stack.empty())return 0;
    return 1;
}

void DPLLSolver::backtrack(int level){

    for(int i=0;i<level;i++){
        info = info_stack.top();
        info_stack.pop();
        literals[info.literal_choice]  = (literals[info.literal_choice]+1)%2;
    }
}