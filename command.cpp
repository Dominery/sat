#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <thread>
#include "command.h"
#include "cnfFileFormatter.h"
#include "DPLLSolver.h"

using namespace std;

void show_processing(bool &running){
    string mark = "\\|/-";
    vector<string> words{"I'm trying hard to solve it ","Maybe you can watch TV first","I feel the answer is coming!","Trust me!Don't shut me down!"};
    int count = 0;
    while(running){
        cout<<mark.at(count%4)<<words[count/5%4]<<"\r";
        count++;
        Sleep(200);
    }
    cout<<"I have completed the task, took a look: \r"<<endl;
}

int ParseFileCommand::execute(CommandInfo&info){
    string filename;
    cout<<"please input file path"<<endl;
    cin>>filename;
    try
    {
        info.formula = CnfFileFormatter(filename).parse();
        info.filename = filename;
    }
    catch(IOException& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 1;
}

int ShowFormulaCommand::execute(CommandInfo&info){
    if(info.formula.not_init()){
        cout<<"please input file first"<<endl;
    }else{
        for(auto clause:info.formula.clauses){
            for(auto literal:clause){
                cout<<DECODE(literal)<<"\t";
            }
            cout<<endl;
        }
    }
    return 1;
}

// get the result of DPLL and show the processing 
SolveResult SolveFormulaCommand::solve_process(Formula &formula){
    SolveResult result;
    if(formula.not_init()){
    cout<<"please input file first"<<endl;
    }else{
        bool running = true;
        thread task(show_processing,std::ref(running)); //create a thread for showing process
        task.detach();
        result = solver_.get_result(formula);
        running = false;
        Sleep(400); // wait the show_running thread completing the cout
    }
    return result;
}

int SolveFormulaCommand::execute(CommandInfo&info){
    SolveResult result = solve_process(info.formula);
    switch (result.status)
    {
    case SATISFIABLE:
        cout<<"Satisfied"<<endl;
        for(auto lit:result.results){
            cout<<lit<<"\t";
        }
        cout<<endl;
        cout<<result.duration<<"ms"<<endl;
        store_result(info.filename,result);
        break;
    case UNSATISFIABLE:
        cout << "Unsatisfied"<<endl;
        break;
    default:
        break;
    }
    return 1;
}

void SolveFormulaCommand::store_result(string filename,SolveResult&result){
    string new_filename = filename.substr(0,filename.rfind('.'))+".res"; //change the extension of filename to res
    ofstream out(new_filename);
    exporter.format(result,out);
    out.close();
}
int ExitCommand::execute(CommandInfo&){
    return 0;
}