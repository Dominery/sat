#include <iostream>
#include <windows.h>
#include <string>

#include "display.h"
#include "formula.h"
#include "cnfFileParser.h"
#include "DPLLSolver.h"
#include "inputHandler.h"
#include "command.h"

using namespace std;

void Display::show_sat(){
    cout<<"\tSAT Solver"<<endl;
    cout<<"1.read file\t2.show formula"<<endl;
    cout<<"3.solve the formula \t0.exit"<<endl;
}

void Display::run(){
    Formula formula;
    InputHandler input_handler;
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
            int mark = command->execute(formula);
            if(mark==0)running=false;
        }
        system("pause");
    }

}



int main(int argc, char const *argv[])
{
    SetConsoleTitle(TEXT("SAT Solver"));
    Display().run();
    return 0;
}
