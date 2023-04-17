#include "Life.hpp"
#include <iostream>
#include <vector>

using namespace std;



int main() {
    int t;
    cin >> t;
    while (t--) {
        run_testcase();
    }

}

void run_testcase() {
    int r, c;
    cin >> r;
    cin  >> c;
    int n_live_cells;
    cin >> n_live_cells;
    vector<pair<int, int>> live_cell_coords(n_live_cells);
    for (int live_cell_idx = 0; live_cell_idx < n_live_cells; ++live_cell_idx) {
        int x, y;
        cin >> x;
        cin >> y;
        live_cell_coords.push_back(pair<int, int>(x, y));
    }
    int n_sims, freq;
    cin >> n_sims;
    cin >> freq;
}