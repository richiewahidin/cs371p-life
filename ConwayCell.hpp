#ifndef CONWAY_CELL_HPP
#define CONWAY_CELL_HPP
#include <iostream>

#include "AbstractCell.hpp"

class ConwayCell : public AbstractCell {

    protected:
        ostream& write (ostream& out) const;

    public:
        ConwayCell() = default;
        ConwayCell(bool);
        int update(int cardinalNeighbors, int diagonalNeighbors);    
        ConwayCell* clone();
        ~ConwayCell() = default;
        
};

#endif