#include <vector>
#include <iostream>
#include "formula.h"
#include "DPLLSolver.h"
#ifndef SUDOKU_H
#define SUDOKU_H
#define ENCODE_CELL(i,j,n) (i*n+j+1)
struct Sudoku
{
    // -1 represent unknown
    // 0 represent false
    // 1 represent true
    std::vector<std::vector<int>> sudoku;
    int size;
    Sudoku(int n){
        for(int i=0;i<n;i++){
            sudoku.push_back(std::vector<int>(n,-1));
        }
        size = n;
    };
    Sudoku(){};
    ~Sudoku(){
    };
    void init(){
        for(auto row:sudoku){
            for(int i=0;i<size;++i){
                row[i]=-1;
            }
        }
    }
    void display(std::ostream&os){
        for(auto row:sudoku){
            for(int i=0;i<size;++i){
                if(row[i]!=-1)os<<row[i]<<" ";
                else os<<"x"<<" ";
            }
            os<<"\n";
        }
    }
};


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
    SudoParser(){};
    ~SudoParser(){};
    Formula parse(Sudoku&sudo);
    Sudoku format(SolveResult&result);
};

class PuzzleGenerator
{
private:
    bool las_vegas(int n,Sudoku&);
    Sudoku puzzle;
    SudoParser parser_;
    DPLLSolver solver_;
public:
    Sudoku generate(int dim);
    PuzzleGenerator(){};
    PuzzleGenerator(SudoParser&parser,DPLLSolver&solver):parser_(parser),solver_(solver){};
    ~PuzzleGenerator(){};
};
#endif