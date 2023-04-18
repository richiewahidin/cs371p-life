#include "FredkinCell.hpp"

ostream& FredkinCell::write (ostream& out) const {
    assert(_age >= 0);
    if (_alive && _age >= 10) {
        return out << '+';
    } else if (_alive) {
        return out << _age;
    } else {
        return out << '-';
    }
}

FredkinCell::FredkinCell(bool alive) : AbstractCell(alive), _age(0) {}

// Fredkin cells only care about cardinal neighbors
int FredkinCell::update(int cardinalNeighbors, int diagonalNeighbors) {
    assert(cardinalNeighbors >= 0);
    if (_alive) {

        // Live cell remain alive
        if (cardinalNeighbors == 1 || cardinalNeighbors == 3) {
            ++_age;
            if (_age == 2) { // for cell toknow when to mutate
                return 2;
            } else {
                return 0;
            }
        
        // Live cell dies
        } else {
            _alive = false;
            return -1;
        }

    } else {

        // Dead cell becomes alive
        if (cardinalNeighbors == 1 || cardinalNeighbors == 3) {
            _alive = true;
            return 1;
        
        // Dead cell remains dead
        } else {
            return 0;
        }
    }
}

FredkinCell* FredkinCell::clone() {
    return new FredkinCell(*this);
}