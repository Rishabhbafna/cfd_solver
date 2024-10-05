#include<bits/stdc++.h>
#include "src/CFDSolver.h"
// build -> g++ main.cpp src/CFDSolver.cpp src/fileWriter.cpp src/cell.cpp src/config.cpp src/initializationHandler.cpp -o main
using namespace std;

int main() {
    cout<<"Starting the CFD solver..."<<endl;
    Config config;
    FileWriter file_writer;
    CFDSolver cfd_solver(config, file_writer);
    cfd_solver.run();
    cout<<"CFD run completed. "<<endl;
}