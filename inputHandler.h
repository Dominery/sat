#include <map>
#include "command.h"
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
class InputHandler
{
private:
    std::map<int,Command*>commands;
    int get_command();
public:
    void add_command(int key,Command* command){
        commands.insert(pair<int,Command*>(key,command));
    };
    Command* handle_input();
    InputHandler(){
        commands[0] = new ExitCommand();
    };
    ~InputHandler(){
        std::map<int,Command*>::iterator iter;
        for(iter=commands.begin();iter!=commands.end();iter++){
            delete iter->second;
        };
    };
};

#endif