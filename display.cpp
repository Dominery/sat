#include <iostream>
#include <windows.h>
#include <string>

#include "display.h"
#include "inputHandler.h"
#include "command.h"
#include "txtExporter.h"
#include "puzzleGenerator.h"

using namespace std;

void Display::show_sat(){
    cout<<"\tSAT Solver"<<endl;
    cout<<"1.read file\t2.show formula"<<endl;
    cout<<"3.solve the formula \t0.exit"<<endl;
}

void Display::run_sat_menu(TxtExporter&exporter){
    CommandInfo info;
    InputHandler input_handler;
    input_handler.add_command(1,new ParseFileCommand());
    input_handler.add_command(2,new ShowFormulaCommand());
    input_handler.add_command(3,new SolveFormulaCommand(exporter));
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
}

void Display::run_sudo_menu(){
    bool running = true;
    int command;
    while(running){
        system("cls");
        show_sudo_menu();
        cin>>command;
        switch (command)
        {
        case 1:
            int dim;
            cin>>dim;
            PuzzleGenerator().generate(dim).display(cout);
            break;
        
        default:
            break;
        }
        system("pause");
    }

}

void Display::show_sudo_menu(){
    cout<<"\tSudo game"<<endl;
    cout<<"1.generate\t2.show answer"<<endl;
}

int main(int argc, char const *argv[])
{
    system("COLOR 97");
    SetConsoleTitle(TEXT("SAT Solver"));
    // TxtExporter exporter(".res");
    // Display().run_sat_menu(exporter);
    Display().run_sudo_menu();
    return 0;
}
