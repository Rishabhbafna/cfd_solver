#include<bits/stdc++.h>
#include "CFDSolver.h"

using namespace std;

void CFDSolver::run() {
    cout<<"Creating grid..."<<endl;
    create_grid();
    cout<<"Grid created. "<<endl;
    cout<<"populating grid..."<<endl;
    populate_grid_with_inital_values();
    cout<<"Grid populated. "<<endl;
    cout<<"evaluating initialization function..."<<endl;
    evaluate_initialization_function();
    cout<<"Evaluated initialization function."<<endl;
    cout<<"writing solution file..."<<endl;
    file_writer_.write_solution_file(grid_, config_, 0.0);
    
}

void CFDSolver::create_grid() {
    cout<<"Creating grid...1"<<endl;
    for (int i = 0; i < config_.get_grid_size(); ++i) {
        grid_.emplace_back(config_); // Use emplace_back to construct objects in place
    }
}

void CFDSolver::populate_grid_with_inital_values() {
    double dx = config_.get_inital_dx();
    for (int i=0; i < grid_.size(); i++) {
        grid_[i] = Cell(config_);
        grid_[i].set_dx(dx);
        grid_[i].set_cx(config_.get_min_x() + dx * (i + 0.5 - config_.get_num_ghost_cells()));
    }
};

void CFDSolver::evaluate_initialization_function() {
    int rk_step = 0;
    for (auto& cell : grid_) {
        cout<<cell<<endl;
        auto& u = cell.get_u();
        u[rk_step] = config_.get_initialization_function().evaluate((cell.get_cx()));
    }
};