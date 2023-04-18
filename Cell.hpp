#ifndef CELL_HPP
#define CELL_HPP

#include <cassert>
#include "AbstractCell.hpp"
#include "ConwayCell.hpp"
#include "FredkinCell.hpp"

class Cell {
    
    friend ostream& operator<<(ostream& lhs, const Cell& rhs) {
        return lhs << rhs;
    };

    private:
        AbstractCell *ptr = nullptr;
    public:
        // Cell() = default;
        Cell(bool isConway);
        Cell(bool isConway, bool isAlive);
        Cell(Cell&& rhs);
        Cell(Cell& rhs);
        Cell& operator=(Cell& rhs);
        Cell& operator=(Cell&&);
        int update (int cardinalNeighbors, int diagonalNeighbors);
        void mutate ();
        void clone(Cell& other);
        ~Cell();
    
};

#endif