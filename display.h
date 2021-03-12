
#ifndef DISPLAY_H
#define DISPLAY_H
class Display
{
private:
    int get_command();
public:
    void show_sat();
    void run();
    Display(){};
    ~Display(){};
};
#endif