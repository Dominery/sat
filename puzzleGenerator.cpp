#include <ctime>
#include <cstdlib>
#include <set>
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <fstream>
#include "sudoku.h"
#include "DPLLSolver.h"
#include "formula.h"
#include "cnfFileFormatter.h"
#include "resultFormatter.h"


using namespace std;

bool PuzzleGenerator::las_vegas(int n,Sudoku& sudo){
    set<int> random_init;
    int num = sudo.size * sudo.size;
    while (random_init.size()!=n)
    {
        int value = rand()%num;
        auto index = random_init.find(value);
        if(index ==random_init.end()){
            random_init.insert(value);
        }
    }
    for(auto i=random_init.begin();i!=random_init.end();++i){
        int row = *i/sudo.size;
        int col = *i%sudo.size;
        sudo.sudoku[row][col] = rand()%2;
    }
    Formula formula = parser_.parse(sudo);

    SolveResult result= solver_.get_result(formula);
    if (result.status==SATISFIABLE){ 
        puzzle = parser_.format(result);
        formula_ = formula;
        return true;
    };
    return false;
}

Sudoku PuzzleGenerator::generate(int dim){
    if(dim%2||dim<5)throw IOException("warning","unsupported dim:"+dim);
    Sudoku sudo(dim);
    srand(time(NULL));
    while (!las_vegas(dim*dim/6,sudo))
    {
        sudo.init();
    }
    return sudo;
}