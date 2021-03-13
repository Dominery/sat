#include <iostream>
#include <windows.h>
#include <string>

#include "display.h"
#include "formula.h"
#include "cnfFileParser.h"
#include "DPLLSolver.h"

using namespace std;

void Display::show_sat(){
    cout<<"\tSAT Solver"<<endl;
    cout<<"1.read file\t2.show formula"<<endl;
    cout<<"3.solve the formula \t4.show result"<<endl;
    cout<<"5.exit"<<endl;
}

int Display::get_command(){
    int command =-1;
    try
    {
        string input;
        cin>>input;
        command = stoi(input);
    }
    catch(const std::exception& e)
    {
        std::cerr << "please input number" << '\n';
        command = -1;
    }
    return command;
    
}

void Display::parse_file(Formula& formula){
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
    system("pause");
}

void Display::show_formula(Formula&formula){
    if(formula.not_init()){
        cout<<"please input file first"<<endl;
    }else{
        for(auto clause:formula.clauses){
            for(auto literal:clause){
                cout<<DECODE(literal);
            }
            cout<<endl;
        }
    }
    system("pause");
}
SolveResult Display::process_formula(Formula&formula){
    SolveResult result;
    if(formula.not_init()){
    cout<<"please input file first"<<endl;
    }else{
        result = DPLLSolver(formula).get_result();
    }
    system("pause");
    return result;
}

void Display::show_result(const SolveResult&result){
    switch (result.status)
    {
    case UNKNOWN:
        cout<<"don't process formula"<<endl;
        break;
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
    system("pause");
}

void Display::run(){
    Formula formula;
    SolveResult result;
    bool running = true;
    while(running){
        system("cls");
        show_sat();       
        int command = get_command();
        switch (command)
        {
        case 1:
            parse_file(formula);
            break;
        case 2:
            show_formula(formula);
        break;
        case 3:
            result = process_formula(formula);
            break;
        case 4:
            show_result(result);
            break;
        case 5:
            running = false;
            break;
        default:
            system("pause");
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
