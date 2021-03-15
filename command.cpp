#include <string>
#include <iostream>
#include <windows.h>
#include <thread>
#include "command.h"
#include "cnfFileParser.h"
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
        result = DPLLSolver(formula).get_result();
        running = false;
        Sleep(200); // wait the show_running thread completing the cout
    }
    return result;
}

int SolveFormulaCommand::execute(Formula&formula){
    SolveResult result = solve_process(formula);
    switch (result.status)
    {
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