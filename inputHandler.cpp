#include <string>
#include <iostream>
#include "inputHandler.h"
#include "command.h"

using namespace std;

int InputHandler::get_command(){
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

Command* InputHandler::handle_input(){
    int command = get_command();
    auto iter = commands.find(command);
    if(iter !=commands.end())return iter->second;
    else return nullptr;
}