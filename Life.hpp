#ifndef LIFE_HPP
#define LIFE_HPP
#include <vector>
// #include "Con.hpp"
#include <iostream>

using namespace std;

template<typename CellType>
class Life {
    private:
        vector<vector<CellType>> grid;
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
                grid(vector<vector<CellType>> (r + 2, vector<CellType> (c + 2))),
                cardinal_neighbor_counts(r + 2, vector<int>(c + 2, 0)),
                diagonal_neighbor_counts(r + 2, vector<int>(c + 2, 0)), 
                population(0) {
            CellType og_live_cell(true);
   
            // for (int i = 0; i < r + 2; ++i) {
            //     vector<CellType> row;
            //     for (int j = 0; j < c + 2; ++j) {
            //         CellType dead_cell(false);
            //         row.push_back(dead_cell);
            //     }
            //     grid.push_back(row);
            // }

            for (size_t index = 0; index < live_cells.size(); ++index) {
                pair<int, int> coords = live_cells[index];
                if (!is_duplicate(live_cells, index)) { // only add live cell if there is not a live cell already
                    grid[coords.first + 1][coords.second + 1] = og_live_cell; // + 1 for extra walls
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
            for (size_t i = 1; i < grid.size() -1; ++i) {
                for (size_t j = 1; j < grid[0].size() - 1; ++j) {
                    int result = grid[i][j].update(cardinal_neighbor_counts[i][j], diagonal_neighbor_counts[i][j]);
                    if (result != 2) {
                        population += result;
                        update_neighbors(pair<int, int>(i, j), result, new_cardinal_neighbor_counts, new_diagonal_neighbor_counts);  
                    } // if result == 2 need to change from fredkin to conway for cell   
                }
            }
            swap(cardinal_neighbor_counts, new_cardinal_neighbor_counts);
            swap(diagonal_neighbor_counts, new_diagonal_neighbor_counts);
        }

        // print function that prints the state of each cell each round
        void print(int curr_round) {
            cout << "Generation = " << curr_round << ", Population = " << population << "." << endl;
            for (size_t i = 1; i < grid.size() - 1; ++i) {
                for (size_t j = 1; j < grid[0].size() - 1; ++j) {
                    cout << grid[i][j];
                }
                cout << endl;
            }
        }





        
        

};

#endif

