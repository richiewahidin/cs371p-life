#ifndef FREDKIN_CELL_HPP
#define FREDKIN_CELL_HPP

#include "AbstractCell.hpp"

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