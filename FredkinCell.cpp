#include "FredkinCell.hpp"

FredkinCell::FredkinCell(bool alive) : AbstractCell(alive), _age(0) {}

FredkinCell::FredkinCell(FredkinCell& other) : AbstractCell(other._alive), _age(other._age) {}

int FredkinCell::update(int n_neighbors) {
    if (_alive) {
        if (n_neighbors == 1 || n_neighbors == 3) {
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
        if (n_neighbors == 1 || n_neighbors == 3) {
            _alive = true;
            return 1;
        } else {
            return 0;
        }
    }
}

FredkinCell& FredkinCell::operator= (FredkinCell&) = default;

FredkinCell* FredkinCell::clone() {
    return new FredkinCell(*this);
}