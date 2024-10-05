#include<bits/stdc++.h>
#include "CFDSolver.h"

using namespace std;

double TimeStepCalculator::calculate_time_step(Config& config, vector<Cell>& grid) {
    //assuming that dx is constant through-out the simulation
    return (grid.front().get_dx() / abs(config.get_advection_velocity())) * config.get_courant_num(); // time = distance/velocity * courant_num
}

void CellProcessor::update_ghost_cells(Config& config, vector<Cell>& grid, int rk_step) {
    for (int ghost_cell = 0; ghost_cell < config.get_num_ghost_cells(); ghost_cell++) {

        grid[ghost_cell].get_u()[rk_step] = grid[config.get_num_x_cells() + ghost_cell].get_u()[rk_step]; //for ghost cells to the right

        grid[config.get_num_x_cells() + config.get_num_ghost_cells() + ghost_cell].get_u()[rk_step] = grid[config.get_num_ghost_cells() + ghost_cell].get_u()[rk_step];
    }
}

void CellProcessor::reconstruct_variables(Config& config, vector<Cell>& grid, int rk_step) {
    for (int i = config.get_num_ghost_cells() - 1; i < config.get_num_x_cells() + config.get_num_ghost_cells() + 1; i++) { //iterate over all internal cells, incl one ghost cells at both boundaries.

        grid[i].set_u_left(grid[i].get_u()[rk_step]);
        grid[i].set_u_right(grid[i].get_u()[rk_step]); //we set them as same for now, we can use different technique like derivative of centroid etc.
    }
}

void CellProcessor::update_cell_averages(Config& config, vector<Cell>& grid, int rk_step, double dt) {
    for (int i = config.get_num_ghost_cells(); i < config.get_num_x_cells() + config.get_num_ghost_cells(); i++) {
        grid[i].get_u()[rk_step + 1] = (grid[i].get_u()[rk_step]) + (dt / grid[i].get_dx() * grid[i].get_total_flux()); //euler time step
    }
}

void FluxCalculator::calculate_flux(Config& config, vector<Cell>& grid, int rk_step) {
    for (auto& cell : grid) {
        cell.set_total_flux(0.0);
    }

    for (int interface_index = config.get_num_ghost_cells(); interface_index < config.get_num_x_cells() + config.get_num_ghost_cells() + 1; interface_index++) { //start from the first internal index till last index that contains internal cells
        double left_value = grid[interface_index - 1].get_u_right();
        double right_value = grid[interface_index].get_u_left();

        //Lax-Friedrichs scheme
        double flux = (0.5 * config.get_advection_velocity() * (left_value + right_value)) - (0.5 * abs(config.get_advection_velocity()) * (right_value - left_value));

        grid[interface_index-1].set_total_flux(grid[interface_index-1].get_total_flux() - flux);
        grid[interface_index].set_total_flux(grid[interface_index].get_total_flux() + flux);
    }
}
void CFDSolver::copy_to_nth_rk_step(int n) {
    for (int i = config_.get_num_ghost_cells(); i < config_.get_num_x_cells() + config_.get_num_ghost_cells(); i++) {
        grid_[i].get_u()[n] = grid_[i].get_u()[config_.get_num_of_rk_steps()];
    }
}

void CFDSolver::run() {
    //init
    InitializationHandler init_handler;
    cout<<"Creating grid..."<<endl;
    init_handler.create_grid(config_, grid_);

    cout<<"populating grid..."<<endl;
    init_handler.populate_grid_with_inital_values(config_, grid_);

    cout<<"evaluating initialization function..."<<endl;
    init_handler.evaluate_initialization_function(config_, grid_);

    time_ = 0.0;

    cout<<"writing initial solution file..."<<endl;
    file_writer_.write_solution_file(grid_, config_, time_);

    TimeStepCalculator time_step_calculator;
    last_time_step_ = false;

    cout<<"Starting the iterations.."<<endl;
    for (int time_iter = 0; time_iter < config_.get_max_time_iterations(); time_iter++ ) {
        double dt = time_step_calculator.calculate_time_step(config_, grid_);
        cout<<"dt : "<<dt<<" at time_iter : "<<time_iter<<endl;
        if (time_ + dt > config_.get_stopping_time()) {
            dt = config_.get_stopping_time() - time_;
            last_time_step_ = true;
        }

        for (int rk_step = 0; rk_step < config_.get_num_of_rk_steps(); rk_step++) {
            CellProcessor cell_processor;
            cell_processor.update_ghost_cells(config_, grid_, rk_step);
            cell_processor.reconstruct_variables(config_, grid_, rk_step);

            FluxCalculator flux;
            flux.calculate_flux(config_, grid_, rk_step);
            cell_processor.update_cell_averages(config_, grid_, rk_step, dt);
        }

        copy_to_nth_rk_step(0);

        time_ += dt;
        if (last_time_step_) {
            break;
        }
        if ((time_iter + 1) % 5 == 0) {
            file_writer_.write_solution_file(grid_, config_, time_);
        }
    }
    cout<<"writing final solution file..."<<endl;
    file_writer_.write_solution_file(grid_, config_, time_);

}
