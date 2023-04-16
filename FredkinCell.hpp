#ifndef FREDKIN_CELL_HPP
#define FREDKIN_CELL_HPP

#include "AbstractCell.hpp"

class FredkinCell : public AbstractCell {

    private:
        int _age;
    public:
        FredkinCell(bool);
        FredkinCell(FredkinCell&);
        int update(int cardinalNeighbors, int diagonalNeighbors);
        FredkinCell& operator= (FredkinCell&);
        FredkinCell* clone ();
        ~FredkinCell() = default;
}

#endif