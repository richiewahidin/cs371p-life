#ifndef ABSTRACT_CELL_HPP
#define ABSTRACT_CELL_HPP
#include <iostream>
using namespace std;

class AbstractCell {

    friend ostream& operator<<(ostream& lhs, const AbstractCell& rhs) {
        return rhs.write(lhs);
    };

    protected:
        bool _alive; // 0 dead 1 alive
        virtual ostream& write (ostream& out) const = 0;

    public:
        AbstractCell() : _alive(false) {};
        AbstractCell(bool alive) : _alive(alive) {};
        virtual int update(int cardinalNeighbors, int diagonalNeighbors) = 0;
        // virtual AbstractCell& operator= (AbstractCell&) = 0;
        virtual AbstractCell* clone() = 0;
        virtual ~AbstractCell() = default;

};


#endif