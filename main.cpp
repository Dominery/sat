#include <iostream>

#include"formula.h"
#include "DPLLSolver.h"
#include "cnfFileParser.h"


using namespace std;

// int main(int argc, char const *argv[])
// {
//     try{
//         Formula formula = CnfFileParser("sat-20.cnf").parse();
//         DPLLSolver solver(formula);
//         Status status = solver.process();
//         // for(auto cl:formula.clauses){
//         //     for(auto value:cl){
//         //         cout<<DECODE(value);
//         //         cout<<"\t";
//         //     }
//         //     cout<<endl;
//         // }
        
//         // cout<<status<<endl;
//         for(int i=0;i<solver.get_current().literals.size();i++){
//             int value = solver.get_current().literals[i]?-(i+1):i+1;
//             cout<<value<<"\t";
//         }
//         cout<<endl;
//     }catch(IOException &e){
//         cout<<e.what()<<endl;
//     }
//     return 0;
// }