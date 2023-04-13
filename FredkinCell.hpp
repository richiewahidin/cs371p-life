#ifndef FREDKIN_CELL_HPP
#define FREDKIN_CELL_HPP

#include "AbstractCell.hpp"

class FredkinCell : public AbstractCell {

    private:
        int _age;
    public:
        FredkinCell(bool);
        bool update(int);
        FredkinCell& operator= (FredkinCell&);
}

#endif