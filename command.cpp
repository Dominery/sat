#include <string>
#include <iostream>
#include "command.h"
#include "cnfFileParser.h"
#include "DPLLSolver.h"

using namespace std;

int ParseFileCommand::execute(Formula&formula){
    string filename;
    cout<<"please input file path"<<endl;
    cin>>filename;
    try
    {
        formula = CnfFileParser(filename).parse();
    }
    catch(IOException& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 1;
}

int ShowFormulaCommand::execute(Formula&formula){
    if(formula.not_init()){
        cout<<"please input file first"<<endl;
    }else{
        for(auto clause:formula.clauses){
            for(auto literal:clause){
                cout<<DECODE(literal);
            }
            cout<<endl;
        }
    }
    return 1;
}

int SolveFormulaCommand::execute(Formula&formula){
    SolveResult result;
    if(formula.not_init()){
    cout<<"please input file first"<<endl;
    }else{
        result = DPLLSolver(formula).get_result();
    }
    switch (result.status)
    {
    case UNKNOWN:
        cout<<"don't process formula"<<endl;
        break;
    case SATISFIABLE:
        cout<<"Satisfied"<<endl;
        for(auto lit:result.results){
            cout<<lit<<"\t";
        }
        cout<<endl;
        cout<<result.duration<<"ms"<<endl;
        break;
    default:
        break;
    }
    return 1;
}

int ExitCommand::execute(Formula&){
    return 0;
}