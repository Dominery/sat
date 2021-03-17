#include "txtExporter.h"
#ifndef DISPLAY_H
#define DISPLAY_H
class Display
{
private:
    void show_sat();
    void show_sudo_menu();
public:
    void run_sat_menu(TxtExporter&);
    void run_sudo_menu();
    Display(){};
    ~Display(){};
};
#endif