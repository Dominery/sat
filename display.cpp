#include <iostream>
#include <windows.h>
#include <string>

#include "display.h"
#include "inputHandler.h"
#include "command.h"
#include "resultFormatter.h"
#include "sudoku.h"
#include "cnfFileFormatter.h"
#include "DPLLSolver.h"

using namespace std;

void Display::show_sat(){
    cout<<"\tSAT Solver"<<endl;
    cout<<"1.read file\t2.show formula"<<endl;
    cout<<"3.solve the formula \t0.back"<<endl;
}

void Display::run_sat_menu(InputHandler&input_handler){
    CommandInfo info;
    input_handler.add_command(0,new ExitCommand());
    input_handler.add_command(1,new ParseFileCommand());
    input_handler.add_command(2,new ShowFormulaCommand());
    input_handler.add_command(3,new SolveFormulaCommand());
    Command * command=nullptr;
    bool running = true;

    while(running){
        system("cls");
        show_sat();
        command = input_handler.handle_input();
        if(command!=nullptr){
            int mark = command->execute(info);
            if(mark==0)running=false;
        }
        system("pause");
    }
    input_handler.clear();
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
}
