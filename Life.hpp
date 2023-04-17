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
        int population;

        // row and column with walls accounted for
        void update_neighbors(
            pair<int, int> coords, 
            int update_amt, 
            vector<vector<int>>& new_cardinal_neighbors, 
            vector<vector<int>>& new_diagonal_neighbors) {

            // update cardinal neighbor counts
            new_cardinal_neighbors[coords.first - 1][coords.second] += update_amt;
            new_cardinal_neighbors[coords.first + 1][coords.second] += update_amt;
            new_cardinal_neighbors[coords.first][coords.second - 1] += update_amt;
            new_cardinal_neighbors[coords.first][coords.second + 1] += update_amt;

            // update diagonal neighbor counts
            new_diagonal_neighbors[coords.first - 1][coords.second - 1] += update_amt;
            new_diagonal_neighbors[coords.first - 1][coords.second + 1] += update_amt;
            new_diagonal_neighbors[coords.first + 1][coords.second - 1] += update_amt;
            new_diagonal_neighbors[coords.first + 1][coords.second + 1] += update_amt;
        }

    public:
        Life(int r, int c, vector<pair<int, int>> live_cells) : 
            grid(r + 2, vector<Cell>(c + 2, Cell(typeid(CellType) == typeid(ConwayCell)))), 
            cardinal_neighbor_counts(r + 2, vector<int>(c + 2, 0)),
            diagonal_neighbor_counts(r + 2, vector<int>(c + 2, 0)), 
            population(0) {
                bool is_conway = typeid(CellType) == typeid(ConwayCell);
                Cell og_live_cell = Cell(is_conway, true);

                for (int index = 0; index < live_cells.sie(); ++index) {
                    if (!is_duplicate(live_cells, index)) { // only add live cell if there is not a live cell already
                        grid[coords.first + 1][coords.second + 1].clone(og_live_cell); // + 1 for extra walls
                        ++population;
                        update_neighbors(pair<int, int>(coords.first+ 1, coords.second + 1), 
                            1, cardinal_neighbor_counts, diagonal_neighbor_counts);
                    }
                }
        }

        // function returns true if there is already a live cell in that spot
        // in the grid, returns false otherwise
        bool is_duplicate(vector<pair<int, int>> live_cells, int index) {
            for (int i = 0; i < index; ++i) {
                if (live_cells[i] == live_cells[index]) {
                    return true;
                }
            }
            return false;
        }

        void do_round() {
            vector<vector<int>> new_cardinal_neighbor_counts = cardinal_neighbor_counts;
            vector<vector<int>> new_diagonal_neighbor_counts = diagonal_neighbor_counts;
            for (int i = 1; i < grid.size() + 1; ++i) {
                for (int j = 1; j < grid[0].size(); ++j) {
                    int result = grid[i][j].update(cardinal_neighbor_counts[i][j], diagonal_neighbor_counts[i][j]);
                    if (result == 2 && typeid(CellType) == typeid(Cell)) {
                        grid[i][j].mutate();
                    } else {
                        update_neighbors(pair<int, int>(i, j), result, new_cardinal_neighbor_counts, new_diagonal_neighbor_counts); 
                    }
                    
                }
            }
            swap(cardinal_neighbor_counts, new_cardinal_neighbor_counts);
            swap(diagonal_neighbor_counts, new_diagonal_neighbor_counts);
        }

        // print function that prints the state of each cell each round
        void print() {
            cout << "Generation = " << curr_round << ", Population = " << population << "." << endl;
            for (int i = 1; i < grid.size() + 1; ++i) {
                for (int j = 1; j < grid[0].size(); ++j) {
                    cout << grid[i][j];
                }
                cout << endl;
            }
            cout << endl;
        }





        
        

};

#endif

