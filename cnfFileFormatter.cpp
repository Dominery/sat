#include<iostream>
#include<fstream>
#include<stdexcept>
#include<string>
#include<vector>

#include"cnfFileFormatter.h"
#include"Formula.h"

using namespace std;


IOException::IOException(string s,string info):runtime_error(s){
    this->info = info;
}
const char* IOException::what(){
    return info.c_str();
}
void CnfFileFormatter::move_to_start(ifstream&fin){
    while(!fin.eof()){
        char c;
        fin >> c;
        if (c == 'c'){
            // char temp[100];
            // fin.getline(temp,100);
            string line;
            getline(fin,line);
        }else if (c=='p')
        {
            string validation; // validate the file contained the 'cnf' key word
            fin >> validation;
            if(validation!="cnf"){
                throw IOException("warning","unexpected char:"+validation);
            }
            break;
        }else{
            throw IOException("warning","unexpected char:"+c);
        }
        
    }
}

clause CnfFileFormatter::parseline(ifstream&fin){
    int value;
    fin>>value;
    clause cl;
    while(value != 0){ // encode the liberal if don't meet 0
        cl.push_back(value);
        fin >> value;
    }
    return cl;
}

// parse all line of liberals
Formula CnfFileFormatter::parse(ifstream&fin){ 
    move_to_start(fin);
    int var,num;
    fin>>var>>num;
    Formula formula(var);

    for(int i=0;i<num;i++){
        formula.add_clause(parseline(fin));
    }
    return formula;
}

void CnfFileFormatter::format(Formula&formula,ostream&os){
    // output the info of formula
    os<<"p cnf "<<formula.literals.size()<<" "<<formula.clauses.size()<<"\n"; 
    
    for(auto clause:formula.clauses){
        for(auto lit:clause){
            os<<DECODE(lit)<<" ";
        }
        os<<0<<"\n";
    }

}