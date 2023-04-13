#include "FredkinCell.hpp"

FredkinCell::FredkinCell(bool alive) : AbstractCell(alive), _age(0) {}

void FredkinCell::update(int n_neighbors) {
    if (_alive) {
        if (n_neighbors == 1 || n_neighbors == 3) {
            ++_age;
        } else {
            _alive = false;
        }
    } else {
        if (n_neighbors == 1 || n_neighbors == 3) {
            _alive = true;
        }
    }
}

FredkinCell& FredkinCell::operator= (FredkinCell&) = default;