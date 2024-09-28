#include<bits/stdc++.h>
#include "fileWriter.h"
using namespace std;

class CFDSolver {
    private:
    vector<Cell> grid_;
    Config config_;
    FileWriter file_writer_;

    public:
    CFDSolver(Config& config, FileWriter& file_writer) {
        config_ = config;
        file_writer_ = file_writer;
        cout<<"Constructing cfd solver"<<endl;
        grid_.reserve(config_.get_grid_size());
    }
    void run();
    void create_grid();
    void populate_grid_with_inital_values();
    void evaluate_initialization_function();

};