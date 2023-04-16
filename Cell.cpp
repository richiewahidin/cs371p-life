#include "ConwayCell.hpp"
#include "FredkinCell.hpp"
#include "Cell.hpp"

Cell::Cell(bool isConway) : Cell(isConway, false) {}

Cell::Cell(bool isConway, bool isAlive) {
    if (isConway) {
        ptr = new ConwayCell(isAlive);
    } else {
        ptr = new FredkinCell(isAlive);
    }
}

int Cell::update (int n_neighbors) {
    return ptr->update(n_neighbors);
}

// only if Life instantiated with Cell and reached the age of 2
void Cell::mutate() {
    // delete the fredkin cell
    delete ptr;
    // create a new conway cell
    ptr = new ConwayCell(true);
}

void Cell::clone(Cell& other) {
    if (ptr) {
        delete ptr;
    }
    ptr = (other.ptr)->clone();
}

Cell::~Cell() {
    if (ptr) {
        delete ptr;
        ptr = nullptr;
    }
}
