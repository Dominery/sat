#include <map>
#include "command.h"
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
class InputHandler
{
private:
    std::map<int,Command*>commands;
public:
    static int get_command();
    void add_command(int key,Command* command){
        commands.insert(std::pair<int,Command*>(key,command));
    };
    void clear(){
        for(auto iter=commands.begin();iter!=commands.end();iter++){
            delete iter->second;
        };
        commands.clear();
    };
    Command* handle_input();
    InputHandler(){};
    ~InputHandler(){
        std::map<int,Command*>::iterator iter;
        for(iter=commands.begin();iter!=commands.end();iter++){
            delete iter->second;
        };
    };
};

#endif