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

CnfFileFormatter::CnfFileFormatter(string filename)
{
    fin.open(filename);
    if(!fin.is_open())throw IOException("error",filename+":not found");
}

CnfFileFormatter::~CnfFileFormatter()
{
    if(fin.is_open())fin.close(); // close the ifstream if the object is destroyed
}
void CnfFileFormatter::move_to_start(){
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

clause CnfFileFormatter::parseline(vector<int> &literal_frequency,int*literal_polarity){
    int value;
    fin>>value;
    clause cl;
    while(value != 0){ // encode the liberal if don't meet 0
        value = ENCODE(value);
        cl.push_back(value);
        literal_frequency[value/2]++;
        value%2?literal_polarity[value/2]--:literal_polarity[value/2]++;
        fin >> value;
    }
    return cl;
}

// parse all line of liberals
Formula CnfFileFormatter::parse(){ 
    move_to_start();
    int var,num;
    fin>>var>>num;
    vector<clause> clauses;
    vector<int> literals(var,-1); 
    vector<int> literal_frequency(var,0);
    int *literal_polarity = new int[var];
    for(int i=0;i<var;i++){
        literal_polarity[i]=0;
    }

    for(int i=0;i<num;i++){
        clauses.push_back(parseline(literal_frequency,literal_polarity));
    }
    Formula formula(clauses,literal_frequency,literals);
    formula.literal_polarity = literal_polarity;
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