#include<bits/stdc++.h>
#include "config.h"
#include "cell.h"
using namespace std;
// vector<vector<double>> coefficients_list = {{1, 2, 3}, {4, 5}, {6}};  // Polynomials for different steps
// vector<double> step_boundaries = {-1, -0.25, 0.25, 1};
class InitializationFunction {
public:
    InitializationFunction() : coefficients_list_({{0}, {1}, {0}}), step_boundaries_({-1, -0.25, 0.25, 1}) {}

    InitializationFunction(const vector<vector<double>>& coefficients_list, const vector<double>& step_boundaries) : coefficients_list_(coefficients_list), step_boundaries_(step_boundaries) {}

    InitializationFunction(const InitializationFunction& other) {
        coefficients_list_ = other.coefficients_list_;
        step_boundaries_ = other.step_boundaries_;
    }

    const vector<vector<double>>& get_coefficients_list() const {
        return coefficients_list_;
    }

    void set_coefficients_list(const vector<vector<double>>& coefficients_list) {
        coefficients_list_ = coefficients_list;
    }

    const vector<double>& get_step_boundaries() const {
        return step_boundaries_;
    }

    void set_step_boundaries(const vector<double>& step_boundaries) {
        step_boundaries_ = step_boundaries;
    }

    double evaluate(double x) const;

private:
    vector<vector<double>> coefficients_list_;
    vector<double> step_boundaries_;
};

class InitializationHandler {
private:
    InitializationFunction init_func_;
public:
    InitializationHandler() : init_func_() {}
    InitializationHandler(const vector<vector<double>>& coefficients_list, const vector<double>& step_boundaries) : init_func_(coefficients_list, step_boundaries) {}
    
    void create_grid(Config& config, vector<Cell>& grid);
    void populate_grid_with_inital_values(Config& config, vector<Cell>& grid);
    void evaluate_initialization_function(Config& config, vector<Cell>& grid);
};