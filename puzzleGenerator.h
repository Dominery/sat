#include "sudoku.h"
#ifndef PUZZLEGENERATOR_H
#define PUZZLEGENERATOR_H

class PuzzleGenerator
{
private:
    bool las_vegas(int n,Sudoku&);
    Sudoku puzzle;
public:
    Sudoku generate(int dim);
    PuzzleGenerator(){};
    ~PuzzleGenerator(){};
};
#endif