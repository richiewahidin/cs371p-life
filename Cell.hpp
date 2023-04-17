#ifndef CELL_HPP
#define CELL_HPP

#include "AbstractCell.hpp"
#include "ConwayCell.hpp"
#include "FredkinCell.hpp"

class Cell {
    
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
        ostream& display(ostream& os);
}

#endif