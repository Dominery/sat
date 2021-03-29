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
    for(int i=0;i<sudo.size;++i){
        random_init.insert(i*(sudo.size+1));
        random_init.insert((i+1)*(sudo.size-1));
    }
    random_choose(n,sudo.size,random_init);
    for(auto i=random_init.begin();i!=random_init.end();++i){
        int row = *i/sudo.size;
        int col = *i%sudo.size;
        sudo.sudoku[row][col] = rand()%2;
    }
    Formula formula = parser_.parse(sudo);
    // ofstream os("test.cnf");
    // CnfFileFormatter().format(formula,os);
    // os.close();
    // return true;
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
    while (!las_vegas(pow(dim-2,2)/3,sudo))
    {
        sudo.init();
    }
    return dig(dim*(dim-2));
}


void PuzzleGenerator::random_choose(int n,int num,set<int>&choices){
    while (choices.size()<n)
    {
        int value = rand()%num;
        auto index = choices.find(value);
        if(index ==choices.end()){
            choices.insert(value);
        }
    }
}

Sudoku PuzzleGenerator::dig(int num_hole){
    set<int> choices;
    int num = puzzle.size*puzzle.size;
    random_choose(num-num_hole,num,choices);
    
    Sudoku sudo(puzzle.size);
    for(auto i=choices.begin();i!=choices.end();++i){
        int row = *i/sudo.size;
        int col = *i%sudo.size;
        sudo.sudoku[row][col] = puzzle.sudoku[row][col];
    }
    return sudo;
}