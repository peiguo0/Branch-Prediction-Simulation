
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
#define TAKEN 1
#define NOTTAKEN 0




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
    
    vector<bitset<2> > saturating_counter;
    saturating_counter.assign(pow(2, M) , 3);       //initialized every counter to 11
    

    
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
            
            bitset<4> temIndex;
            long PredictIndex=0;
            int index=0;        //used for count the 4 LSBs
            
            while (index!=4) {
                temIndex[index] = accessaddr[index];
                index+=1;
            }
            
            PredictIndex = temIndex.to_ulong();

            //saturating counter reading, to get the prediction of current branch
            if (saturating_counter[PredictIndex] == 0 or saturating_counter[PredictIndex] == 1){
                TakenPrediction = NOTTAKEN;
            }
            
            if (saturating_counter[PredictIndex] == 2 or saturating_counter[PredictIndex] == 3){
                TakenPrediction = TAKEN;
            }


            
            //saturating coutner modify
            if (TakenResult == "0")     //the TakenResult is 0 (not taken)
            {
                if (saturating_counter[PredictIndex] == 0){
                    //00
                    saturating_counter[PredictIndex] = 0;
                }
                
                if (saturating_counter[PredictIndex] == 1){
                    //01
                    saturating_counter[PredictIndex] = 0;
                }
                
                if (saturating_counter[PredictIndex] == 2){
                    //10
                    saturating_counter[PredictIndex] = 0;
                }
                
                if (saturating_counter[PredictIndex] == 3){
                    //11
                    saturating_counter[PredictIndex] = 2;
                }
                

            
            }
            
            
            else                //the TakenResult is 1(Taken)
            {
                if (saturating_counter[PredictIndex] == 0){
                    //00
                    saturating_counter[PredictIndex] = 1;
                }
                
                if (saturating_counter[PredictIndex] == 1){
                    //01
                    saturating_counter[PredictIndex] = 3;
                }
                
                if (saturating_counter[PredictIndex] == 2){
                    //10
                    saturating_counter[PredictIndex] = 3;
                }
                
                if (saturating_counter[PredictIndex] == 3){
                    //11
                    saturating_counter[PredictIndex] = 3;
                }
            
            }
            
            
            tracesout<< TakenPrediction << endl;  // Output whether this branch is predicted TAKEN or NOT TAKEN
            
        }
        traces.close();
        tracesout.close();
    }
    else cout<< "Unable to open trace or traceout file ";
    
    
    return 0;
}
