#include<fstream>
#include<string>
#include<stdexcept>
#include <ostream>

#ifndef PARSER_H
#define PARSER_H


#include"formula.h"

class CnfFileFormatter
{
private:
    std::ifstream fin;
    void move_to_start(); // read the comments of cnf file if meet the unsupported syntax throw IOException
    clause parseline(std::vector<int>&,int[]);
public:
    CnfFileFormatter(std::string);
    CnfFileFormatter(){};
    ~CnfFileFormatter();
    Formula parse(); // parse the cnf file data to Formula struct
    void format(Formula&formula,std::ostream&os);
};

class IOException:public std::runtime_error { //if can not read data from file correctly throw the exception
    private:
    std::string info;
    public:
    IOException(std::string s,std::string info);
    const char* what();
    ~IOException(){};
};
#endif