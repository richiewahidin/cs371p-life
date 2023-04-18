#ifndef ABSTRACT_CELL_HPP
#define ABSTRACT_CELL_HPP
#include <iostream>
using namespace std;

class AbstractCell {

    friend ostream& operator<<(ostream& lhs, const AbstractCell& rhs) {
        return rhs.write(lhs);
    };

    protected:
        bool _alive; // 0 dead 1 alive
        virtual ostream& write (ostream& out) const = 0;

    public:
        AbstractCell() : _alive(false) {};
        AbstractCell(bool alive) : _alive(alive) {};
        virtual int update(int cardinalNeighbors, int diagonalNeighbors) = 0;
        // virtual AbstractCell& operator= (AbstractCell&) = 0;
        virtual AbstractCell* clone() = 0;
        virtual ~AbstractCell() = default;

};


#endif

#ifndef CONWAY_CELL_HPP
#define CONWAY_CELL_HPP
#include <iostream>


class ConwayCell : public AbstractCell {
    protected:
        ostream& write (ostream& out) const;
    public:
        ConwayCell() = default;
        ConwayCell(bool);
        // ConwayCell(ConwayCell&);
        // ConwayCell& operator=(ConwayCell& rhs);
        int update(int cardinalNeighbors, int diagonalNeighbors);    
        ConwayCell* clone();
        ~ConwayCell() = default;
};

#endif

ConwayCell::ConwayCell(bool alive) : AbstractCell(alive){}

// ConwayCell::ConwayCell(ConwayCell& other) : AbstractCell(other._alive){} 

// ConwayCell& ConwayCell::operator=(ConwayCell& rhs) = default;

int ConwayCell::update(int cardinalNeighbors, int diagonalNeighbors) {
    int totalNeighbors = cardinalNeighbors + diagonalNeighbors;
    if (_alive && totalNeighbors != 2 && totalNeighbors != 3) {
        _alive = false;
        return -1;
    } else if (!_alive && totalNeighbors == 3) {
        _alive = true;
        return 1;
    }
    return 0;
}

ConwayCell* ConwayCell::clone() {
    return new ConwayCell(*this);
}

ostream& ConwayCell::write (ostream& out) const {
    char symbol = _alive ? '*' : '.';
    return out << symbol;
};
#ifndef FREDKIN_CELL_HPP
#define FREDKIN_CELL_HPP


class FredkinCell : public AbstractCell {

    private:
        int _age;
    public:
        FredkinCell() = default;
        FredkinCell(bool);
        int update(int cardinalNeighbors, int diagonalNeighbors);
        // FredkinCell& operator= (FredkinCell&);
        FredkinCell* clone ();
        ~FredkinCell() = default;
        ostream& write (ostream& out) const;
};

#endif

FredkinCell::FredkinCell(bool alive) : AbstractCell(alive), _age(0) {}

int FredkinCell::update(int cardinalNeighbors, int diagonalNeighbors) {
    if (_alive) {
        if (cardinalNeighbors == 1 || cardinalNeighbors == 3) {
            ++_age;
            if (_age == 2) {
                return 2;
            } else {
                return 0;
            }
        } else {
            _alive = false;
            return -1;
        }
    } else {
        if (cardinalNeighbors == 1 || cardinalNeighbors == 3) {
            _alive = true;
            return 1;
        } else {
            return 0;
        }
    }
}

// FredkinCell& FredkinCell::operator= (FredkinCell&) = default;

FredkinCell* FredkinCell::clone() {
    return new FredkinCell(*this);
}

ostream& FredkinCell::write (ostream& out) const {
    if (_alive && _age >= 10) {
        return out << '+';
    } else if (_alive) {
        return out << _age;
    } else {
        return out << '-';
    }
}
#ifndef CELL_HPP
#define CELL_HPP

#include <cassert>

class Cell {
    
    friend ostream& operator<<(ostream& lhs, const Cell& rhs) {
        return lhs << *(rhs.ptr);
    };

    private:
        AbstractCell *ptr = nullptr;
    public:
        Cell();
        Cell(bool alive);
        // Cell(bool isConway, bool isAlive);
        Cell(Cell&& rhs);
        Cell(const Cell& rhs);
        Cell& operator=(Cell& rhs);
        Cell& operator=(Cell&&);
        int update (int cardinalNeighbors, int diagonalNeighbors);
        void mutate ();
        void clone(Cell& other);
        ~Cell();
    
};

#endif


Cell::Cell() : Cell::Cell(false) { }

Cell::Cell(bool alive) { ptr = new FredkinCell(alive); }

// Cell::Cell(bool isConway, bool isAlive) {
//     if (isConway) {
//         ptr = new ConwayCell(isAlive);
//     } else {
//         ptr = new FredkinCell(isAlive);
//     }
//     assert(ptr);
// }

Cell::Cell(const Cell& rhs) {
    ptr = (rhs.ptr)->clone();
}

Cell::Cell(Cell&& rhs) {
    std::swap((*this).ptr, rhs.ptr);
}

Cell& Cell::operator=(Cell& rhs) {
    if (ptr) {
        delete ptr;
        ptr = nullptr;
    }
    ptr = (rhs.ptr)->clone();
    return *this;
}

Cell& Cell::operator=(Cell&& rhs) {
    Cell that(std::move(rhs));
    std::swap((*this).ptr, that.ptr);
    return *this;
}

int Cell::update (int cardinalNeighbors, int diagonalNeighbors) {
    assert(ptr);
    int result = ptr->update(cardinalNeighbors, diagonalNeighbors);
    if (result == 2) {
        mutate();
        return 0;
    }
    return result;
}

// only if Life instantiated with Cell and reached the age of 2
void Cell::mutate() {
    assert(ptr);
    // delete the fredkin cell
    delete ptr;
    // create a new conway cell
    ptr = new ConwayCell(true);
}

void Cell::clone(Cell& other) {
    if (ptr) {
        delete ptr;
    }
    ptr = (other.ptr)->clone();
}

Cell::~Cell() {
    if (ptr) {
        delete ptr;
        ptr = nullptr;
    }
}
#ifndef LIFE_HPP
#define LIFE_HPP
#include <vector>
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
            if (n_sims - curr_round >= freq) { // curr_round != n_sims
                cout << endl;
            }
        }
        life.do_round();
        
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


