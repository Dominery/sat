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

