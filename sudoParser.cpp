#include <cmath>
#include "formula.h"
#include "sudoku.h"
using namespace std;

vector<vector<int>> dfs(vector<int>,int);

Formula SudoParser::parse(){
    int num = pow(sudoku.size,2)*(sudoku.size-1)*3 + pow(sudoku.size,2);
    Formula formula(num);

    rule_0(formula);
    rule_1(formula);
    rule_2(formula);
    rule_3(formula);
    return formula;
}

void SudoParser::rule_0(Formula&formula){
    for(int i=0;i<dim;i++){
        for(int j=0;j<dim;j++){
            if(sudoku.sudoku[i][j]!=-1){
                int value = ENCODE_CELL(i,j,dim);
                value = sudoku.sudoku[i][j]?value:-value;
                formula.add_clause({value});
            }
        }
    }
}

void SudoParser::rule_1(Formula&formula){
    for(int i=0;i<dim;i++){   // process continuous num in every row 
        for(int j=0;j<dim-2;j++){
            formula.add_clause({ENCODE_CELL(i,j,dim),ENCODE_CELL(i,j+1,dim),ENCODE_CELL(i,j+2,dim)});
            formula.add_clause({-ENCODE_CELL(i,j,dim),-ENCODE_CELL(i,j+1,dim),-ENCODE_CELL(i,j+2,dim)});
        }
    }
    for(int j=0;j<dim;j++){
        for(int i=0;i<dim-2;i++){
            formula.add_clause({ENCODE_CELL(i,j,dim),ENCODE_CELL(i+1,j,dim),ENCODE_CELL(i+2,j,dim)});
            formula.add_clause({-ENCODE_CELL(i,j,dim),-ENCODE_CELL(i+1,j,dim),-ENCODE_CELL(i+2,j,dim)});
        }
    }
}

void SudoParser::rule_3(Formula&formula){
    int count=dim*dim;
    for(int i=0;i<dim;i++){
        for(int k=i+1;k<dim;k++){
           for(int j=0;j<dim;++j){
               rule_3_helper({ENCODE_CELL(i,j,dim),ENCODE_CELL(k,j,dim),++count},formula);
               rule_3_helper({-ENCODE_CELL(i,j,dim),-ENCODE_CELL(k,j,dim),++count},formula);
               ++count;
               rule_3_helper({-(count-2),-(count-1),-count},formula);
           }
           vector<int> lits;int temp = count;
           for(int i=0;i<dim;++i,temp-=3){
               lits.push_back(temp);
           }
           formula.add_clause(lits);
        }
    }

    for(int j=0;j<dim;j++){
        for(int k=j+1;k<dim;k++){
           for(int i=0;i<dim;++i){
               rule_3_helper({ENCODE_CELL(i,j,dim),ENCODE_CELL(k,j,dim),++count},formula);
               rule_3_helper({-ENCODE_CELL(i,j,dim),-ENCODE_CELL(k,j,dim),++count},formula);
                ++count;
               rule_3_helper({-(count-2),-(count-1),-count},formula);
           }
            vector<int> lits;int temp = count;
           for(int i=0;i<dim;++i,temp-=3){
               lits.push_back(temp);
           }
           formula.add_clause(lits);
        }
    }

}

void SudoParser::rule_3_helper(vector<int>lits,Formula&formula){
    formula.add_clause({lits[0],-lits[2]});
    formula.add_clause({lits[1],-lits[2]});
    formula.add_clause({-lits[0],-lits[1],lits[2]});
}

void SudoParser::rule_2(Formula&formula){
    vector<int> lit;
    for(int i=0;i<dim;++i){
        lit.push_back(i);
    }
    auto combs = dfs(lit,dim/2+1);

    for(int i=0;i<dim;++i){
        for(auto comb:combs){
            auto lit = comb;
            for(auto &l:lit){
                l = ENCODE_CELL(i,l,dim);
            }
            formula.add_clause(lit);
            lit = comb;
            for(auto &l:lit){
                l = ENCODE_CELL(l,i,dim);
            }
            formula.add_clause(lit);
        }
    }
}
void dfs_helper(vector<int> input,int need,int remain,vector<int>b,vector<vector<int>>&result,int start=0)
{
        if(remain<0) return;
        if(remain==0)
        {
            result.push_back(b);
            return;
        }
        for(int j=start;j<input.size();j++)
        {
            b[need-remain]=input[j]; 
            dfs_helper(input,need,remain-1,b,result,j+1); 
        }
            
}

vector<vector<int>> dfs(vector<int>literals,int need){
    vector<vector<int>> result;
    dfs_helper(literals,need,need,vector<int>(need),result);
    return result;

}
