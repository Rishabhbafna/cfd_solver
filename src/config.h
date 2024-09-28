#include<bits/stdc++.h>
#include "initializationFunction.h"
using namespace std;

class Config {
public:
    Config() : num_x_cells_(100), num_ghost_cells_(3), num_of_rk_steps_(1), stopping_time_(2.0), max_time_iterations_(100000), min_x_(-1.0), max_x_(1.0), initialization_function_(), base_path_(".") {
        cout<<"config constructor"<<endl;
    }

    Config(int num_x_cells, int num_ghost_cells, int num_of_rk_steps, double stopping_time, int max_time_iterations, double min_x, double max_x, InitializationFunction initialization_function, string base_path) : num_x_cells_(num_x_cells), num_ghost_cells_(num_ghost_cells), num_of_rk_steps_(num_of_rk_steps), stopping_time_(stopping_time), max_time_iterations_(max_time_iterations), min_x_(min_x), max_x_(max_x), initialization_function_(initialization_function), base_path_(base_path) {}

    Config(const Config& other) {
        num_x_cells_ = other.num_x_cells_;
        num_ghost_cells_ = other.num_ghost_cells_;
        num_of_rk_steps_ = other.num_of_rk_steps_;
        stopping_time_ = other.stopping_time_;
        max_time_iterations_ = other.max_time_iterations_;
        min_x_ = other.min_x_;
        max_x_ = other.max_x_;
        initialization_function_ = other.initialization_function_;
        base_path_ = other.base_path_;
    }

    int get_num_x_cells() const { return num_x_cells_; }
    void set_num_x_cells(int num_x_cells) { num_x_cells_ = num_x_cells; }

    int get_num_ghost_cells() const { return num_ghost_cells_; }
    void set_num_ghost_cells(int num_ghost_cells) { num_ghost_cells_ = num_ghost_cells; }

    int get_num_of_rk_steps() const { return num_of_rk_steps_; }
    void set_num_of_rk_steps(int num_of_rk_steps) { num_of_rk_steps_ = num_of_rk_steps; }

    double get_stopping_time() const { return stopping_time_; }
    void set_stopping_time(double stopping_time) { stopping_time_ = stopping_time; }

    int get_max_time_iterations() const { return max_time_iterations_; }
    void set_max_time_iterations(int max_time_iterations) { max_time_iterations_ = max_time_iterations; }

    double get_min_x() const { return min_x_; }
    void set_min_x(double min_x) { min_x_ = min_x; }

    double get_max_x() const { return max_x_; }
    void set_max_x(double max_x) { max_x_ = max_x; }

    InitializationFunction get_initialization_function() const { return initialization_function_; }
    void set_initialization_function(InitializationFunction initialization_function) { initialization_function_ = initialization_function; }

    string get_base_path() const { return base_path_; }
    void set_base_path(string base_path) {
        base_path_ = base_path;
    }

    int get_grid_size() const { return num_x_cells_ + 2*num_ghost_cells_; }
    double get_inital_dx () const { return (max_x_ - min_x_) / num_x_cells_; }

private:
    int num_x_cells_;
    int num_ghost_cells_;
    int num_of_rk_steps_;
    double stopping_time_;
    int max_time_iterations_;
    double min_x_;
    double max_x_;
    InitializationFunction initialization_function_;
    string base_path_;
};