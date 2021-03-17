#include <ctime>
#include <cstdlib>
#include <set>
#include <stdexcept>
#include <cmath>
#include "puzzleGenerator.h"
#include "sudoku.h"
#include "sudoParser.h"
#include "DPLLSolver.h"
#include "formula.h"


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
    Formula formula = SudoParser(sudo).parse();
    if (DPLLSolver(formula).get_result().status==SATISFIABLE)return true;
    return false;
}

Sudoku PuzzleGenerator::generate(int dim){
    if(dim%2||dim<5)throw runtime_error("unsupported dim:"+dim);
    Sudoku sudo(dim);
    srand(time(NULL));
    while (!las_vegas(pow(dim-2,2)/3,sudo))
    {
        sudo.init();
    }
    
    return sudo;
}