
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

#define TAKEN 1
#define NOTTAKEN 0


int main(int argc, char* argv[]){
    
    int M=0;
    
    ifstream cache_params;
    cache_params.open(argv[1]);

    while(!cache_params.eof())  // read config file, get m
    {
        cache_params>>M;
    }
    
    vector<bitset<2> > saturating_counter;
    saturating_counter.assign(pow(2, M) , 3);       //initialized every counter to 11
    

    
    int TakenPrediction = 0; //can be 0(predict Not taken) or 1(predict taken)
    
    
    ifstream traces;
    ofstream tracesout;
    string outname;
    outname = string(argv[2]) + ".out";
    traces.open(argv[2]);
    tracesout.open(outname.c_str());
    
    string line;
    string TakenResult;    // the result (Taken or Not Taken)
    string xaddr;          // the address from the memory trace store in hex format
    unsigned int addr;     // the address from the memory trace store in unsigned int
    bitset<32> accessaddr; // the address from the memory trace store in the bitset<32>
    
    //long line_number=0; //used for calculate mis-prediction rate
    //long mis_number=0;
    
    if (traces.is_open()&&tracesout.is_open()){
        while (getline (traces,line)){   // read mem access file and access Cache
            
            //line_number+=1;     //count the number of lines (to calculate the mis-prediction rate)
            
            istringstream iss(line);
            if (!(iss >> xaddr >> TakenResult)) {break;}
            stringstream saddr(xaddr);
            saddr >> std::hex >> addr;
            accessaddr = bitset<32> (addr);         //transform hex format to bitset<32>
            
            bitset<32> temIndex;    //to save m bits LSBs
            long PredictIndex=0;    //long int format index, used for locating saturating counter
            int index=0;            //used for count the m bits LSBs
            
            while (index != M) {
                temIndex[index] = accessaddr[index];
                index+=1;
            }
            
            PredictIndex = temIndex.to_ulong();     //transfer bitset to long int format

            //read saturating counter, to get the prediction of current branch
            if (saturating_counter[PredictIndex] == 0 or saturating_counter[PredictIndex] == 1){
                //if saturating counter is 00 or 01
                TakenPrediction = NOTTAKEN;
                
            }
            
            if (saturating_counter[PredictIndex] == 2 or saturating_counter[PredictIndex] == 3){
                //if saturating counter is 10 or 11
                TakenPrediction = TAKEN;
            }

            
            //modify saturating coutner
            if (TakenResult == "0")     //if the TakenResult is 0 (not taken)
            {
                if (saturating_counter[PredictIndex] == 0){
                    //00
                    saturating_counter[PredictIndex] = 0;
                    
                }
                
                else if (saturating_counter[PredictIndex] == 1){
                    //01
                    saturating_counter[PredictIndex] = 0;
                }
                
                else if (saturating_counter[PredictIndex] == 2){
                    //10
                    saturating_counter[PredictIndex] = 0;
                    //mis_number += 1;    //mis-prediction
                }
                
                else if (saturating_counter[PredictIndex] == 3){
                    //11
                    saturating_counter[PredictIndex] = 2;
                    //mis_number += 1;    //mis-prediction
                }
            
            }
            
            
            else                //if the TakenResult is 1(Taken)
            {
                if (saturating_counter[PredictIndex] == 0){
                    //00
                    saturating_counter[PredictIndex] = 1;
                    //mis_number += 1;    //mis-prediction
                }
                
                else if (saturating_counter[PredictIndex] == 1){
                    //01
                    saturating_counter[PredictIndex] = 3;
                    //mis_number += 1;    //mis-prediction
                }
                
                else if (saturating_counter[PredictIndex] == 2){
                    //10
                    saturating_counter[PredictIndex] = 3;
                }
                
                else if (saturating_counter[PredictIndex] == 3){
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
    
    //std::cout<<(double)mis_number/line_number;      //output the result of mis-prediction rate
    
    return 0;
}
