#include "Life.hpp"
#include "FredkinCell.hpp"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void run_testcase() {
    // Get size of grid and number of live cells
    int r, c;
    cin >> r;
    cin  >> c;
     int n_live_cells;
    cin >> n_live_cells;

    // Get the coordinates of the live cells
    vector<pair<int, int>> live_cell_coords;
    for (int live_cell_idx = 0; live_cell_idx < n_live_cells; ++live_cell_idx) {
        int x, y;
        cin >> x;
        cin >> y;
        live_cell_coords.push_back(pair<int, int>(x, y));
    }

    // Get number of simulations and print frequency
    int n_sims, freq;
    cin >> n_sims;
    cin >> freq;

    Life<FredkinCell> life(r, c, live_cell_coords);
    cout << "*** Life<FredkinCell> " << r << "x" << c << " ***" << endl;
    cout << endl;  

    // Run rounds 
    for (int curr_round = 0; curr_round <= n_sims; ++curr_round) {
        if (curr_round % freq == 0) {
            life.print(curr_round);

            // Print new line if it is not the last print of the current simulation
            if (n_sims - curr_round >= freq) {
                cout << endl;
            }
        }

        life.do_round();
        
    }
}

int main() {
    int t;
    cin >> t;

    // Repeat for number of testscases
    while (t--) {
        run_testcase();
        if (t) {
            cout << endl;
        }
    }
}