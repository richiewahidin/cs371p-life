#ifndef CELL_HPP
#define CELL_HPP

#include <cassert>
#include "AbstractCell.hpp"
#include "ConwayCell.hpp"
#include "FredkinCell.hpp"

class Cell {
    
    friend ostream& operator<<(ostream& lhs, const Cell& rhs) {
        return lhs << *(rhs.ptr);
    };

    private:
        AbstractCell *ptr = nullptr;
        
    public:
        Cell();
        Cell(bool alive);
        Cell(const Cell& rhs);
        Cell& operator=(Cell& rhs);
        int update (int cardinalNeighbors, int diagonalNeighbors);
        void mutate ();
        void clone(Cell& other);
        ~Cell();
    
};

#endif