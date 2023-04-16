#ifndef LIFE_HPP
#define LIFE_HPP
#include <vector>
#include "Cell.hpp"

using namespace std;

template<typename CellType>
class Life {
    private:
        vector<vector<Cell>> grid;
        vector<vector<int>> cardinal_neighbor_counts;
        vector<vector<int>> diagonal_neighbor_counts;

        // row and column with walls accounted for
        void update_neighbors(pair<int, int> coords, int update_amt) {

            // update cardinal neighbor counts
            cardinal_neighbor_counts[coords.first - 1][coords.second] += update_amt;
            cardinal_neighbor_counts[coords.first + 1][coords.second] += update_amt;
            cardinal_neighbor_counts[coords.first][coords.second - 1] += update_amt;
            cardinal_neighbor_counts[coords.first][coords.second + 1] += update_amt;

            // update diagonal neighbor counts
            diagonal_neighbor_counts[coords.first - 1][coords.second - 1] += update_amt;
            diagonal_neighbor_counts[coords.first - 1][coords.second + 1] += update_amt;
            diagonal_neighbor_counts[coords.first + 1][coords.second - 1] += update_amt;
            diagonal_neighbor_counts[coords.first + 1][coords.second + 1] += update_amt;
        }

    public:
        // TODO remember to modify Cell update signature to take two ints
        Life(int r, int c, vector<pair<int, int>> live_cells) : 
            grid(r + 2, vector<Cell>(c + 2, Cell(typeid(CellType) == typeid(ConwayCell)))), 
            cardinal_neighbor_counts(r + 2, vector<int>(c + 2, 0)),
            diagonal_neighbor_counts(r + 2, vector<int>(c + 2, 0))
            {
                bool is_conway = typeid(CellType) == typeid(ConwayCell);
                Cell og_live_cell = Cell(is_conway, true);
                for (pair<int, int> coords : live_cells) {
                    grid[coords.first + 1][coords.second + 1].clone(og_live_cell); // + 1 for extra walls
                    update_neighbors(pair<int, int>(coords.first+ 1, coords.second + 1), 1);
                }
        }



        
        

};

#endif

