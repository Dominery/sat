#include<iostream>
#include<fstream>
#include<exception>
#include<string>
#include<vector>

#include"cnfFileParser.h"
#include"Formula.h"

using namespace std;

class IOException:public runtime_error{ //if can not read data from file correctly throw the exception
    private:
    string info;
    public:
    IOException(string s,string info);
    const char* what();
    ~IOException(){};
};
IOException::IOException(string s,string info):runtime_error(s){
    this->info = info;
}
const char* IOException::what(){
    return info.c_str();
}

CnfFileParser::CnfFileParser(string filename)
{
    fin.open(filename);
    if(!fin.is_open())throw IOException("error",filename+":not found");
}

CnfFileParser::~CnfFileParser()
{
    if(fin.is_open())fin.close(); // close the ifstream if the object is destroyed
}
void CnfFileParser::move_to_start(){
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

clause CnfFileParser::parseline(vector<int> &literal_frequency){
    int value;
    fin>>value;
    clause cl;
    while(value != 0){ // encode the liberal if don't meet 0
        // if(value>0){
        //     cl.push_back(2*(value-1)); // encode all positive liberal as even start at 0
        //     literal_frequency[value-1]++; 
        // }else{
        //     cl.push_back(2*(-1*value)-1); // encode all negative liberal as obb start at 1
        //     literal_frequency[-value-1]++;
        // }
        value = ENCODE(value);
        cl.push_back(value);
        literal_frequency[value/2]++;
        fin >> value;
    }
    return cl;
}

// parse all line of liberals
Formula CnfFileParser::parse(){ 
    move_to_start();
    int var,num;
    fin>>var>>num;
    vector<clause> clauses;
    vector<int> literals(var,-1); 
    vector<int> literal_frequency(var,0);

    for(int i=0;i<num;i++){
        clauses.push_back(parseline(literal_frequency));
    }
    return Formula(clauses,literal_frequency,literals);
}

int main(int argc, char const *argv[])
{
    Formula formula;
    try{
        formula = CnfFileParser("sat-20.cnf").parse();
        for(auto cl:formula.clauses){
            for(auto value:cl){
                cout<<DECODE(value);
                cout<<"\t";
            }
            cout<<endl;
        }
    }catch(IOException &e){
        cout<<e.what()<<endl;
    }
    return 0;
}
