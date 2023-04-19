#ifndef ABSTRACT_CELL_HPP
#define ABSTRACT_CELL_HPP
#include <iostream>
#include <cassert>
using namespace std;

class AbstractCell {

    friend ostream& operator<<(ostream& lhs, const AbstractCell& rhs) {
        return rhs.write(lhs);
    };

    protected:
        bool _alive; // 0 dead 1 alive
        virtual ostream& write (ostream&) const = 0;

    public:
        AbstractCell();
        AbstractCell(bool alive);
        virtual int update(int cardinalNeighbors, int diagonalNeighbors) = 0;
        virtual AbstractCell* clone() = 0;
        virtual ~AbstractCell() = default;

};

#endif