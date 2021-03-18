#include <string>
#include <fstream>
#include <iostream>
#include "resultFormatter.h"
#include "DPLLSolver.h"
using namespace std;

SolveResult ResultFormatter::parse(ifstream& fin){
    SolveResult result;
    string mark;
    fin>>mark;
    if(mark=="s"){
        int complete;
        fin>>complete;
        result.status = complete >0?SATISFIABLE:UNSATISFIABLE;
    }

    fin>>mark;
    if(mark=="v"){
        vector<int> results;
        int value;
        fin>>mark;
        while(mark!="t"){
            results.push_back(stoi(mark));
            fin>>mark;
        }
        result.results = results;
    }
    return result;

}

void ResultFormatter::format(SolveResult&result,ostream&os){
    os << "s\t"<<(result.status==UNSATISFIABLE?0:1)<<endl;
    os <<"v"<<"\n";
    for(int i=0;i<result.results.size();i++){
        if(i%20==0&&i!=0)os<<result.results[i]<<endl;
        else{
            os<<result.results[i]<<" ";
        }
    }
    os<<endl;
    os<<"t\t"<<result.duration<<"ms"<<endl;   
}