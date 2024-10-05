#include<bits/stdc++.h>
#include "fileWriter.h"
#include "initializationHandler.h"
using namespace std;

class TimeStepCalculator {
public:
    double calculate_time_step(Config& config, vector<Cell>& grid);
};
class CellProcessor {
public:
    void update_ghost_cells(Config& config, vector<Cell>& grid, int rk_step);
    void reconstruct_variables(Config& config, vector<Cell>& grid, int rk_step);
    void update_cell_averages(Config& config, vector<Cell>& grid, int rk_step, double dt);
};
class FluxCalculator {
public:
    void calculate_flux(Config& config, vector<Cell>& grid, int rk_step);
};


class CFDSolver {
private:
    vector<Cell> grid_;
    Config config_;
    FileWriter file_writer_;
    double time_ = 0.0;
    bool last_time_step_ = false;

public:
    CFDSolver(Config& config, FileWriter& file_writer) {
        config_ = config;
        file_writer_ = file_writer;
        cout<<"Constructing cfd solver"<<endl;
        grid_.reserve(config_.get_grid_size());
    }
    void run();
    void copy_to_nth_rk_step(int n = 0);
};