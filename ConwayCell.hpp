#ifndef CONWAY_CELL_HPP
#define CONWAY_CELL_HPP

#include "AbstractCell.hpp"

class ConwayCell : public AbstractCell {

    public:
        ConwayCell(bool);
        ConwayCell(ConwayCell&);
        ConwayCell& operator=(ConwayCell& rhs);
        int update(int cardinalNeighbors, int diagonalNeighbors);    
        ConwayCell* clone();
        ~ConwayCell() = default;
};

#endif