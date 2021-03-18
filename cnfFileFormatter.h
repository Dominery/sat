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
    void move_to_start(std::ifstream&fin); // read the comments of cnf file if meet the unsupported syntax throw IOException
    clause parseline(std::vector<int>&,int[],std::ifstream&fin);
public:
    CnfFileFormatter(){};
    ~CnfFileFormatter(){};
    // parse the cnf file data to Formula struct
    Formula parse(std::ifstream&fin); 
    // transfer data of formula as output stream
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
