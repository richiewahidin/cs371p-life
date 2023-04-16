#ifndef LIFE_HPP
#define LIFE_HPP
#include <vector>
#include "Cell.hpp"

using namespace std;

template<typename CellType>
class Life {
    private:
        vector<vector<Cell>> grid;
        vector<vector<pair<int, int>>> neighbor_counts;

    public:
        // TODO implement the constructors
        // TODO remember to modify Cell update signature to take two ints
        // TODO make default constructor for Cell that makes nullptr
        // TODO update all Cell methods to check whether the ptr is null
        Life(int r, int c, vector<pair<int, int>> live_cells);
};

#endif

