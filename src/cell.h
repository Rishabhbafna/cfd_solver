#pragma once
#include <bits/stdc++.h>
#include "config.h"

using namespace std;

class Cell {
public:
    Cell(const Config& config) : u_(config.get_num_of_rk_steps() + 1), u_left_(0.0), u_right_(0.0), cx_(0.0), dx_(0.0) {}

    Cell(const vector<double>& u, double u_left, double u_right, double cx, double dx) : u_(u), u_left_(u_left), u_right_(u_right), cx_(cx), dx_(dx) {}

    Cell(const Cell& other) {
        u_ = other.u_;
        u_left_ = other.u_left_;
        u_right_ = other.u_right_;
        cx_ = other.cx_;
        dx_ = other.dx_;
    }

    const vector<double>& get_u() const { return u_; }
    void set_u(const vector<double>& u) { u_ = u; }

    double get_u_left() const { return u_left_; }
    void set_u_left(double u_left) { u_left_ = u_left; }

    double get_u_right() const { return u_right_; }
    void set_u_right(double u_right) { u_right_ = u_right; }

    double get_cx() const { return cx_; }
    void set_cx(double cx) { cx_ = cx; }

    double get_dx() const { return dx_; }
    void set_dx(double dx) { dx_ = dx; }

private:
    vector<double> u_;
    double u_left_;
    double u_right_;
    double cx_;
    double dx_;
};