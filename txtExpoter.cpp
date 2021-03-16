#include <string>
#include <fstream>
#include "txtExporter.h"
#include "DPLLSolver.h"
using namespace std;

void TxtExporter::output(string filename,SolveResult&result){
    string new_filename = filename.substr(0,filename.rfind('.'))+extension;
    ofstream out(new_filename);
    if(!out.is_open())return;
    out << "s\t"<<(result.status==UNSATISFIABLE?0:1)<<endl;
    out <<"v\t";
    for(int i=0;i<result.results.size();i++){
        if(i%20==0&&i!=0)out<<endl;
        else{
            out<<result.results[i]<<" ";
        }
    }
    out<<endl;
    out<<"t\t"<<result.duration<<"ms"<<endl;
}