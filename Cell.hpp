#ifndef CELL_HPP
#define CELL_HPP

#include "AbstractCell.hpp"

class Cell {
    
    private:
        AbstractCell *ptr = nullptr;
    public:
        Cell(bool isConway);
        Cell(bool isConway, bool isAlive);
        int update (int);
        void mutate ();
        void clone(Cell& other);
        ~Cell();
}

#endif