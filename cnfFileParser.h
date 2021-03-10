

#ifndef PARSER_H
#define PARSER_H
#include<fstream>
#include<string>


#include"formula.h"

class CnfFileParser
{
private:
    std::ifstream fin;
    void move_to_start(); // read the comments of cnf file if meet the unsupported syntax throw IOException
    clause parseline(std::vector<int>&);
public:
    CnfFileParser(std::string);
    ~CnfFileParser();
    Formula parse(); // parse the cnf file data to Formula struct
};
#endif
