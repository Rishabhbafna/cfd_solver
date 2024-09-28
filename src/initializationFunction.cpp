#include<bits/stdc++.h>
#include "initializationFunction.h"
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