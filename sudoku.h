#include <vector>
#include <iostream>
#ifndef SUDOKU_H
#define SUDOKU_H

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


#endif