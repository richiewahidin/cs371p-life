#include "Life.hpp"
#include <iostream>
#include <vector>

using namespace std;
// ostream& cout = cout;
void run_testcase() {

    // get input
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

    Life<ConwayCell> life(r, c, live_cell_coords);
    cout << "*** Life<ConwayCell> " << r << "x" << c << " ***" << endl;
    cout << endl;
    
    // run rounds 
    for (int curr_round = 0; curr_round < n_sims; ++curr_round) {
        if (curr_round % freq == 0) {
            life.print(curr_round);
        }
        life.do_round();
    }

}

int main() {
    int t;
    cin >> t;
    cout << t << endl;
    while (t--) {
        run_testcase();
    }

}

