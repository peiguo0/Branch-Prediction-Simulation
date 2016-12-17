
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include <cmath>
#include <bitset>

using namespace std;
//access state:
#define TAKEN  0 // no action
#define NOT TAKEN 1 // read hit



//int main(int argc, char* argv[]){
int main(){
    
    int M=0;

    ifstream cache_params;
    //cache_params.open(argv[1]);
    cache_params.open("/Users/gpz/Desktop/Lab3/Lab3/config.txt");

    while(!cache_params.eof())  // read config file, get m
    {
        cache_params>>M;
    }
    
    
    
    // Implement by you:

    
    
    
    int TakenPrediction = 0; //can be 0(predict Not taken) or 1(predict taken)
    
    
    ifstream traces;
    ofstream tracesout;
    string outname;
    //outname = string(argv[2]) + ".out";
    outname = "/Users/gpz/Desktop/Lab3/Lab3/traceout.txt";
    //traces.open(argv[2]);
    traces.open("/Users/gpz/Desktop/Lab3/Lab3/trace.txt");
    tracesout.open(outname.c_str());
    
    string line;
    string TakenResult;  // the result (Taken or Not Taken)
    string xaddr;       // the address from the memory trace store in hex;
    unsigned int addr;  // the address from the memory trace store in unsigned int;
    bitset<32> accessaddr; // the address from the memory trace store in the bitset32;
    
    if (traces.is_open()&&tracesout.is_open()){
        while (getline (traces,line)){   // read mem access file and access Cache
            
            istringstream iss(line);
            if (!(iss >> xaddr >> TakenResult)) {break;}
            stringstream saddr(xaddr);
            saddr >> std::hex >> addr;
            accessaddr = bitset<32> (addr);
            
            std::cout<<accessaddr;
            std::cout<<"\n";
            std::cout<<TakenResult;
            std::cout<<"\n";
            
            

            if (TakenResult == "0")     //the TakenResult is 0 (not taken)
            {

            
            }
            
            
            else                //the TakenResult is 1(Taken)
            {

            
                
            }
            
            
            
            tracesout<< TakenPrediction << endl;  // Output whether this branch is predicted TAKEN or NOT TAKEN
            
        }
        traces.close();
        tracesout.close();
    }
    else cout<< "Unable to open trace or traceout file ";
    
    
    
    
    
    return 0;
}
