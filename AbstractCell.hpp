#ifndef ABSTRACT_CELL_HPP
#define ABSTRACT_CELL_HPP
#include <iostream>
using namespace std;

class AbstractCell {

    protected:
        bool _alive; // 0 dead 1 alive
    public:
        AbstractCell(bool alive) : _alive(alive) {};
        virtual int update(int cardinalNeighbors, int diagonalNeighbors) = 0;
        // virtual AbstractCell& operator= (AbstractCell&) = 0;
        virtual AbstractCell* clone() = 0;
        virtual ~AbstractCell() = default;
        virtual ostream& display(ostream& os) = 0;

};


#endif