#include <cmath>
#include "sudoku.h"
#include "DPLLSolver.h"

using namespace std;

Sudoku SudoFormatter::format(SolveResult&result,int dim){
    Sudoku sudo(dim);
    for(int i=0;i<dim*dim;++i){
        int row = i/dim;
        int line = i%dim;
        sudo.sudoku[row][line] = result.results[i]>0?1:0;
    }
    return sudo;
}