#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

#include "display.h"
#include "inputHandler.h"
#include "command.h"
#include "resultFormatter.h"
#include "sudoku.h"
#include "cnfFileFormatter.h"
#include "DPLLSolver.h"
#include "satState.h"

using namespace std;

void Display::show_sat(){
    cout<<"\tSAT Solver"<<endl;
    cout<<"1.read file\t2.show formula"<<endl;
    cout<<"3.solve the formula\t4.validate the answer"<<endl;
    cout<<"5.store the result\t0.back"<<endl;
}

void Display::run_sat_menu(InputHandler&input_handler){
    Sat sat;

    while(true){
        system("cls");
        show_sat();
        int input = input_handler.get_command();
        if(input==0)break;
        sat.handleInput((Input)input);
        system("pause");
    }
}

void Display::run_sudo_menu(InputHandler&input_handler){
    CommandInfo info;
    input_handler.add_command(0,new ExitCommand());
    input_handler.add_command(1,new GenerateSudoCommand());
    Command *command = nullptr;
    bool running = true;

    while(running){
        system("cls");
        show_sudo_menu();
        command = input_handler.handle_input();
        if(command!=nullptr){
            int mark = command->execute(info);
            if(mark==0)running=false;
        }        
        system("pause");
    }
    input_handler.clear();
}

void Display::show_sudo_menu(){
    cout<<"\tSudo game"<<endl;
    cout<<"1.generate\t0.back"<<endl;
}

void Display::run_main_menu(){
    InputHandler input_handler;
    bool running = true;
    while(running){
        system("cls");
        cout<<"\t Sat and Sudoku"<<endl;
        cout<<"1.Sat\t2.sudoku\t0.exit"<<endl;
        switch (input_handler.get_command())
        {
        case 1:
            run_sat_menu(input_handler);
            break;
        case 2:
            run_sudo_menu(input_handler);
            break;
        case 0:
            running = false;
            break;
        default:
            break;
        }
    }
}

Display::Display(){
    system("COLOR 97");
    SetConsoleTitle(TEXT("SAT And Sudo"));
    PlaySound(TEXT("src/hopper.wav"), NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);
    vector<string> words = {"loading music please wait"};
    bool running = true;
    thread task(show_processing,std::ref(running),std::ref(words));
    task.detach();
    Sleep(1000);
    running = false;
}
