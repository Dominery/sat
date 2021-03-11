#include<vector>
#include<algorithm>
#include "DPLLSolver.h"
using namespace std;


DPLLSolver::DPLLSolver(Formula& formula):current_node(formula)
{
}

DPLLSolver::~DPLLSolver()
{
}

Formula DPLLSolver::get_current(){
    return current_node;
}

Status DPLLSolver::process(){
    Status status = preprocess();
    if(status != UNKNOWN)return status;
    while (1)
    {
        int literal = decide_next_branch();
        while (true)
        {
            status = deduce(literal);
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

Status DPLLSolver::single_clause(Formula& formula){
    if(formula.clauses.size()==0)return SATISFIABLE;
    // single_found will be true until the formula doesn't have single clauses
    bool single_found = true;
    while (single_found)
    {
        single_found = false;
        auto clause_num = formula.clauses.size();
        for(int i=0;i<clause_num;i++){
            if(formula.clauses[i].size()==1){
                single_found = true;
                int literal = formula.clauses[i][0];
                formula.literals[literal/2] = literal%2;
                formula.literal_frequency[literal/2]=-1; // mark the literal frequency
                Status status = transform_clauses(formula,literal/2);
                if (status==UNKNOWN)break;
                else return status;
            }
        }
    }
    return UNKNOWN;
    
}

Status DPLLSolver::transform_clauses(Formula &formula,int literal){
    int value_of_literal = formula.literals[literal]; // 0 true;1 false
    for(int i=0;i<formula.clauses.size();i++){
        for(int j=0;j<formula.clauses[i].size();j++){
            if(2*literal+value_of_literal==formula.clauses[i][j]){
                formula.clauses.erase(formula.clauses.begin()+i);
                i--;
                if(formula.clauses.size()==0)return SATISFIABLE;
                break;
            }else if(literal==formula.clauses[i][j]/2){
                formula.clauses[i].erase(formula.clauses[i].begin()+j);
                j--;
                if(formula.clauses[i].size()==0)return UNSATISFIABLE;
            }
        }
    }
    return UNKNOWN;
}

Status DPLLSolver::preprocess(){
    Status status = single_clause(current_node);
    fstack.push(current_node);
    return status;
}

int DPLLSolver::decide_next_branch(){
    //find the literal with maximum frequency in current formula
    int i = distance(current_node.literal_frequency.begin(),
    max_element(current_node.literal_frequency.begin(),current_node.literal_frequency.end()));
    current_node.literals[i] = 1;
    current_node.literal_frequency[i] = -1;
    fstack.push(current_node);
    current_node.literals[i]=0;
    return i;
}

Status DPLLSolver::deduce(int literal){
    Status status = transform_clauses(current_node,literal);
    if (status==UNSATISFIABLE)return CONFLICT;
    status = single_clause(current_node);
    if(status == UNSATISFIABLE)return CONFLICT;
    return status;
}

int DPLLSolver::analyze_conflict(){
    if(fstack.size()==1)return 0;
    return 1;
}

void DPLLSolver::backtrack(int level){
    for(int i=0;i<level;i++){
        current_node = fstack.top();
        fstack.pop();
    }
}