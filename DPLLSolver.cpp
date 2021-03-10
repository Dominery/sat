#include "DPLLSolver.h"

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