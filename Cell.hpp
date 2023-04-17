#ifndef CELL_HPP
#define CELL_HPP

#include "AbstractCell.hpp"
#include "ConwayCell.hpp"
#include "FredkinCell.hpp"

class Cell {
    
    friend ostream& operator<<(ostream& lhs, const AbstractCell& rhs) {
        return rhs.ptr->write(lhs);
    };

    private:
        AbstractCell *ptr = nullptr;
    public:
        // Cell() = default;
        Cell(bool isConway);
        Cell(bool isConway, bool isAlive);
        int update (int cardinalNeighbors, int diagonalNeighbors);
        void mutate ();
        void clone(Cell& other);
        ~Cell();
    
}

#endif