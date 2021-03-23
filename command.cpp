#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <thread>
#include <ctime>
#include "command.h"
#include "inputHandler.h"
#include "cnfFileFormatter.h"
#include "DPLLSolver.h"
#include "sudoku.h"
#include "formula.h"

using namespace std;

void show_processing(bool &running,vector<string>&words){
    string mark = "\\|/-";
    int count = 0;
    while(running){
        cout<<mark.at(count%4)<<words[count/5%words.size()]<<"\r";
        count++;
        Sleep(200);
    }
}

int ParseFileCommand::execute(CommandInfo&info){
    string filename;
    cout<<"please input file path"<<endl;
    cin>>filename;
    ifstream fin(filename);
    try
    {
        if(!fin.is_open())throw IOException("warning","file:"+filename+" not exit");
        info.formula = file_formatter.parse(fin);
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
        int i=0;
        for(auto clause:info.formula.clauses){
            if(i++>20)break;
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
        vector<string> words{"I'm trying hard to solve it ","Maybe you can watch TV first","I feel the answer is coming!","Trust me!Don't shut me down!"};
        thread task(show_processing,std::ref(running),std::ref(words)); //create a thread for showing process
        task.detach();
        result = DPLLSolver().get_result(formula);
        running = false;
        Sleep(400); // wait the show_running thread completing the cout
        cout<<"I have completed the task, took a look: \r"<<endl;
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
        info.result = result;
        break;
    case UNSATISFIABLE:
        cout << "Unsatisfied"<<endl;
        cout<<result.duration<<"ms"<<endl;
        store_result(info.filename,result);
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

int GenerateSudoCommand::execute(CommandInfo&info){
    cout<<"input the dim :";
    int dim = InputHandler::get_command();
    try{
        vector<string> words = {"one more second  ","it will come soon","I'm trying hard  "};
        bool running = true;
        thread task(show_processing,std::ref(running),std::ref(words));
        task.detach();

        clock_t start = clock();
        Sudoku sudo= generator.generate(dim);
        running = false;
        clock_t end = clock();
        auto duration = end - start;
        Sleep(duration/10);
        cout<< duration<<"ms"<<endl;
        Sudoku answer = generator.get_answer();
        sudo.display(cout);
        play_sudo(answer,sudo);
        cout<<"press any key to see answer"<<endl;
        string str;
        cin>>str;
        answer.display(cout);
    }catch(IOException&e){
        cout<<e.what()<<endl;
    }
    return 1;
}

void GenerateSudoCommand::play_sudo(Sudoku&sudo,Sudoku&puzzle){
    cout<<"please input row col value to play:like 1 1 0"<<endl;
    cout<<"input -1 to exit"<<endl;
    while(true){
        int row ,col,value;
        cin>>row;
        if(row==-1)break;
        cin>>col>>value;
        if(sudo.sudoku[row-1][col-1]==value){
            cout<<"right"<<endl;
            puzzle.sudoku[row-1][col-1] = value;
        }else{
            cout<<"wrong answer"<<endl;
        }
        if(puzzle.is_unsure()){
            puzzle.display(cout);
        }else{
            cout<<"great you have completed the sudo"<<endl;
            break;
        }
        
    }
}

int ValidateCommand::execute(CommandInfo&info){
    if(info.formula.not_init()||info.result.status==UNKNOWN){
        return 1;
    }
    vector<int> literals = formatter.format(info.result);
    bool validation = true;
    for(auto clause:info.formula.clauses){
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
    return 1;
}

