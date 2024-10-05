#include<bits/stdc++.h>
#include "initializationHandler.h"
using namespace std;

double InitializationFunction::evaluate(double x) const {
    if (x < step_boundaries_.front() || x > step_boundaries_.back()) {
        cerr << "Warning: x value (" << x << ") is out of bounds. Returning 0." << endl;
        return 0.0;
    }

    int step_index = 0;
    while (step_index < step_boundaries_.size() - 1 && x >= step_boundaries_[step_index]) {
        step_index++;
    }

    const vector<double>& coefficients = coefficients_list_[step_index-1];
    double result = 0.0;
    for (int i = 0; i < coefficients.size(); i++) {
        result += coefficients[i] * pow(x, i);
    }
    return result;
}

void InitializationHandler::create_grid(Config& config, vector<Cell>& grid) {
    cout<<"Creating grid...1"<<endl;
    for (int i = 0; i < config.get_grid_size(); ++i) {
        grid.emplace_back(config); // Use emplace_back to construct objects in place
    }
}

void InitializationHandler::populate_grid_with_inital_values(Config& config, vector<Cell>& grid) {
    double dx = config.get_inital_dx();
    for (int i=0; i < grid.size(); i++) {
        grid[i] = Cell(config);
        grid[i].set_dx(dx);
        grid[i].set_cx(config.get_min_x() + dx * (i + 0.5 - config.get_num_ghost_cells()));
    }
};

void InitializationHandler::evaluate_initialization_function(Config& config, vector<Cell>& grid) {
    int rk_step = 0;
    for (auto& cell : grid) {
        cout<<cell<<endl;
        auto& u = cell.get_u();
        u[rk_step] = init_func_.evaluate((cell.get_cx()));
    }
};