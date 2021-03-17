#include <vector>
#include "formula.h"
#include "sudoku.h"
#ifndef SUDOPARSER_H
#define SUDOPARSER_H

#define ENCODE_CELL(i,j,n) (i*n+j+1)
class SudoParser
{
private:
    Sudoku sudoku;
    int dim;
    // process initialed 1 or 0 in puzzle
    void rule_0(Formula&);
     // there are no three continuous 1 or 0 in every columns or every rows 
    void rule_1(Formula&);
    // there are no same rows or columns
    void rule_3(Formula&);
    void rule_3_helper(std::vector<int>,Formula&);
    // every column and row must have same  number of 1 and 0
    void rule_2(Formula&);
public:
    SudoParser(Sudoku&sudo):sudoku(sudo){dim=sudo.size;};
    ~SudoParser(){};
    Formula parse();
};

#endif