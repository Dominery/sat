#include <iostream>
#include <windows.h>

#include "display.h"
#include "formula.h"
#include "cnfFileParser.h"
#include "DPLLSolver.h"

using namespace std;

void Display::show_sat(){
    cout<<"\tSAT Solver"<<endl;
    cout<<"1.read file\t2.show formula"<<endl;
    cout<<"3.solve the formula \t4.show result"<<endl;
}

int Display::get_command(){
    int command =-1;
    try
    {
        cin>>command;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return command;
    
}

void Display::run(){
    Formula formula;
    DPLLSolver solver;
    Status status=UNKNOWN;
    bool running = true;
    while(running){
        system("cls");
        show_sat();       
        int command = get_command();
        string filename;
        switch (command)
        {
        case 1:
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
            
            break;
        if(formula.not_init()){
            cout<<"please input file first";
            break;
        }
        case 2:
            for(auto clause:formula.clauses){
                for(auto literal:clause){
                    cout<<DECODE(literal);
                }
                cout<<endl;
            }
            system("pause");
        break;
        case 3:
            solver = DPLLSolver(formula);
            status = solver.process();
            break;

        case 4:
            switch (status)
            {
            case UNKNOWN:
                cout<<"don't process formula"<<endl;
                break;
            case SATISFIABLE:
                cout<<"Satisfied"<<endl;
                for(int i=0;i<solver.get_current().literals.size();i++){
                    int value = solver.get_current().literals[i]?-(i+1):i+1;
                    cout<<value<<"\t";
                }
                cout<<endl;
                break;
            default:
                break;
            }
            system("pause");
            break;
        default:
            break;
        }
    }

}



int main(int argc, char const *argv[])
{
    SetConsoleTitle(TEXT("SAT Solver"));
    Display().run();
    return 0;
}
