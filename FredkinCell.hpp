#ifndef FREDKIN_CELL_HPP
#define FREDKIN_CELL_HPP

#include "AbstractCell.hpp"

class FredkinCell : public AbstractCell {

    private:
        int _age;

    protected:
        ostream& write (ostream& out) const;

    public:
        FredkinCell() = default;
        FredkinCell(bool alive);
        int update(int cardinalNeighbors, int diagonalNeighbors);
        FredkinCell* clone ();
        ~FredkinCell() = default;
        
};

#endif