#include "FredkinCell.hpp"

FredkinCell::FredkinCell(bool alive) : AbstractCell(alive), _age(0) {}

FredkinCell::FredkinCell(FredkinCell& other) : AbstractCell(other._alive), _age(other._age) {}

int FredkinCell::update(int cardinalNeighbors, int diagonalNeighbors) {
    if (_alive) {
        if (cardinalNeighbors == 1 || cardinalNeighbors == 3) {
            ++_age;
            if (_age == 2) {
                return 2;
            } else {
                return 0;
            }
        } else {
            _alive = false;
            return -1;
        }
    } else {
        if (cardinalNeighbors == 1 || cardinalNeighbors == 3) {
            _alive = true;
            return 1;
        } else {
            return 0;
        }
    }
}

// FredkinCell& FredkinCell::operator= (FredkinCell&) = default;

FredkinCell* FredkinCell::clone() {
    return new FredkinCell(*this);
}

ostream& FredkinCell::write (ostream& out) const {
    char symbol; 
    if (_alive && _age >= 10) {
        return out << '+';
    } else if (_alive) {
        return out << _age;
    } else {
        return out << '-';
    }
}