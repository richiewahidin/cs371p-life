#include "Life.hpp"
#include "ConwayCell.hpp"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
// ofstream& debug;
void run_testcase(ostream& debug) {
    // get input
    int r, c;
    cin >> r;
    cin  >> c;

    int n_live_cells;
    cin >> n_live_cells;
    vector<pair<int, int>> live_cell_coords;
    // live_cell_coords.capacity(n_live_cells);
    debug << "Live cell coords:" << endl;
    debug << "Number of live cell coordinates reading: " << n_live_cells << endl;
    for (int live_cell_idx = 0; live_cell_idx < n_live_cells; ++live_cell_idx) {
        int x, y;
        cin >> x;
        cin >> y;
        live_cell_coords.push_back(pair<int, int>(x, y));
        debug << "x, y = " << x << ", " << y << endl;
    }
    debug << "size of coord vector: " << live_cell_coords.size() << endl;
    int n_sims, freq;
    cin >> n_sims;
    cin >> freq;

    
    
    debug << "n_sims: " << n_sims << ", freq: " << freq << endl;
    debug << endl;


    Life<ConwayCell> life(r, c, live_cell_coords);
    cout << "*** Life<ConwayCell> " << r << "x" << c << " ***" << endl;
    cout << endl;    
    // run rounds 
    for (int curr_round = 0; curr_round <= n_sims; ++curr_round) {
        if (curr_round % freq == 0) {
            life.print(curr_round);
        }
        life.do_round();
        if (curr_round != n_sims) {
            cout << endl;
        }
    }
    debug << endl;

}

int main() {
    ofstream debug;
    debug.open("debug.txt");
    debug << "Writing this to a file.\n";
  
    int t;
    cin >> t;
    while (t--) {
        run_testcase(debug);
        if (t) {
            cout << endl;
        }
    }
    debug.close();

}

