#ifndef CONWAY_CELL_HPP
#define CONWAY_CELL_HPP

#include "AbstractCell.hpp"

class ConwayCell : public AbstractCell {
    public:
        ConwayCell(bool);
        ConwayCell& operator=(ConwayCell& rhs);
        void update(int n_neighbors);    
};

#endif