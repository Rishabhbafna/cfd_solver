#include <bits/stdc++.h>
#include "cell.h"
using namespace std;

class FileWriter {
    private:
    int file_counter_ ;

    public:
    FileWriter() {
        // Initialize member variables here
        file_counter_ = 0;
        cout<<"file writer constructor"<<endl;
    }
    void write_solution_file(vector<Cell> grid, Config config, double time, string filename="Solution");

};