# Branch-Prediction-Simulation
## What is this?
- This is a simulation of branch prediction with 2-bits saturating counter.
- Branch predictor can be used to predict a branch instruction  is taken or not taken when dealing instruction with pipeline.

## What dose this repository have
- **main.cpp:**
- **config.txt:** This is a config file which contains a single line with the value of *m*.
- **trace.txt:** This trace file contains one branch per line,  each line has the PC for the corresponding branch (in hex format) followed by a single bit indicating Taken(1) or Not Taken(0). This is a trace file used in the simulation of branch prediction. **main.cpp** will read this file line by line to find out the pattern of branch and make prediction. The saturating counter will be updated base on **trace.txt**.
- **trace.txt.out:** This file lists the prediction of every line in **trace.txt**. *1* represents **predict taken** and *0* represents **predict not taken**.

## About saturating counter
- Each saturating counter has four state: **11**, **10**, **01**, **00**, represents **Strong Confidence In Taken**, **Weak Confidence In Taken**, **Weak Confidence In Not Taken**, **Strong confidence in Not Taken** [Picture Link][1]
- This design consists of *2^m* 2-bits saturating counter indexed using *m* **LSBs** of each branch instruction.
- Each saturating counter starts with *11*(Predict Taken with High Confidence).

## How to run
- Make sure these files are in the same path
- Use command `g++ main.cpp -m32 -o branchsimulator.out` to compile.
- Use command `./branchsimulator.out config.txt trace.txt` to run.
- The output file **trace.txt.out** will be generated under the same folder.

## mis-prediction rate
- You can also use **main.cpp:** to calculate the *mis-prediction rate* of the input trace file **trace.txt** and the input config file **config.txt:**.


[1]:	https://en.wikipedia.org/wiki/Branch_predictor#/media/File:Branch_prediction_2bit_saturating_counter-dia.svg