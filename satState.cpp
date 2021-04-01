#include <string>
#include <iostream>
#include <thread>
#include <windows.h>
#include "formula.h"
#include "satState.h"
using namespace std;
Sat::Sat(){
    state_= new InitState();
}
void Sat::handleInput(Input input){
    SatState* new_state = state_->handleInput(input);
    if(new_state!=nullptr){
        delete state_;
        state_ = new_state;
        update();
        cout<<"execute command successfully"<<endl;
        return;
    }
    cout<<"please press permitted command"<<endl;
}

SatState* ReadFileState::handleInput(Input input){
    SatState* new_state = nullptr;
    switch (input)
    {
    case SHOWFORMULA:
        new_state =  new ShowFormulaState();
        break;
    case SOLVE:
        new_state = new SolveState();
        break;
    default:
        break;
    }
    return new_state;
}

void ReadFileState::update(Sat&sat){
    string filename;
    cout<<"please input file path"<<endl;
    cin>>filename;
    ifstream fin(filename);
    try
    {
        if(!fin.is_open())throw IOException("warning","file:"+filename+" not exit");
        sat.formula = formatter.parse(fin);
        sat.filename = filename;
    }
    catch(IOException& e)
    {
        std::cerr << e.what() << '\n';
        update(sat);
    }
}

SatState* ShowFormulaState::handleInput(Input input){
    SatState* new_state = nullptr;
    if(input==SOLVE)new_state = new SolveState();
    return new_state;
}

void ShowFormulaState::update(Sat&sat){
    int i=0;
    for(auto clause:sat.formula.clauses){
        if(i++>20)break;
        for(auto literal:clause){
            cout<<DECODE(literal)<<"\t";
        }
        cout<<endl;
    }
}

SatState* SolveState::handleInput(Input input){
    SatState* new_state = nullptr;
    switch (input)
    {
    case VALIDATE:
        new_state = new ValidateState();
        break;
    case READFile:
        new_state = new ReadFileState();
        break;
    case STORE:
        new_state = new StoreState();
        break;
    default:
        break;
    }
    return new_state;
}

void SolveState::update(Sat&sat){
    SolveResult result = solve_process(sat.formula);
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
    case UNSATISFIABLE:
        cout << "Unsatisfied"<<endl;
        cout<<result.duration<<"ms"<<endl;
        break;
    default:
        break;
    }
    sat.result = result;
}

SatState* ValidateState::handleInput(Input input){
    SatState* new_state = nullptr;
    switch (input)
    {
    case READFile:
        new_state = new ReadFileState();
        break;
    case STORE:
        new_state = new StoreState();
        break;
    default:
        break;
    }
    return new_state;
}

void ValidateState::update(Sat&sat){
    if(sat.result.status!=SATISFIABLE)return;
    vector<int> literals = formatter.format(sat.result);
    bool validation = true;
    for(auto clause:sat.formula.clauses){
        bool clause_validation = false;
        for(auto li:clause){
            if(literals[li/2]+(li/2)*2==li){
                clause_validation = true;
                break;
            }
        }
        if(!clause_validation){
            validation = false;
            break;
        }
    }
    if(validation){
        cout<<"validated result:true"<<endl;
    }else{
        cout<<"validated result:false"<<endl;
    }
}

SatState*StoreState::handleInput(Input input){
    SatState* new_sate = nullptr;
    switch (input)
    {
    case VALIDATE:
        new_sate = new ValidateState();
        break;
    case READFile:
        new_sate = new ReadFileState();
        break;
    default:
        break;
    }
    return new_sate;
}

void StoreState::update(Sat&sat){
    string filename = sat.filename;
    string new_filename = filename.substr(0,filename.rfind('.'))+".res"; //change the extension of filename to res
    ofstream out(new_filename);
    exporter.format(sat.result,out);
    out.close();
}


SolveResult SolveState::solve_process(Formula&formula){
    SolveResult result;
    bool running = true;

    vector<string> words{"I'm trying hard to solve it ","Maybe you can watch TV first","I feel the answer is coming!","Trust me!Don't shut me down!"};
    thread task(show_processing,std::ref(running),std::ref(words)); //create a thread for showing process
    task.detach();
    result = solver.get_result(formula);
    running = false;
    Sleep(400); // wait the show_running thread completing the cout
    cout<<"I have completed the task, took a look: \r"<<endl;

    return result;
}