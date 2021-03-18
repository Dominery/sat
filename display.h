#include "DPLLSolver.h"
#include "inputHandler.h"
#ifndef DISPLAY_H
#define DISPLAY_H
class Display
{
private:
    void show_sat();
    void show_sudo_menu();
    void run_sat_menu(InputHandler&input_handler);
    void run_sudo_menu(InputHandler&input_handler);
public:
    void run_main_menu();
    Display();
    ~Display(){};
};
#endif