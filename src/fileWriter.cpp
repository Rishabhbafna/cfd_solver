#include <bits/stdc++.h>
#include "fileWriter.h"
using namespace std;

void FileWriter::write_solution_file(vector<Cell> grid, Config config, double time, string filename) {
    int rk_step = 0;
    string file_path = config.get_base_path() + filename + to_string(file_counter_) + ".out";
    std::ofstream outfile(file_path);

    if (!outfile.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return;
    }
    cout<<"Successfully created a output file : "<<file_path <<endl;
    outfile <<"Number of X cells : " << config.get_num_x_cells() << std::endl;
    outfile <<"Number of ghost cells : " << config.get_num_ghost_cells() << std::endl;
    outfile <<"Time : " << time << std::endl;

    for (Cell& cell : grid) {
        outfile << cell.get_cx() << " : " << cell.get_u()[rk_step] << std::endl;
        cout << cell.get_cx() << " : " << cell.get_u()[rk_step] << std::endl;
    }

    outfile.close();
    file_counter_++;
};