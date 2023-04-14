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

bool Cell::update (int n_neighbors) {
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
    if (!ptr) {
        // other is a ConwayCell
        if (typeid(*(other.ptr)) == typeid(ConwayCell)) {
            ptr = new ConwayCell();

        } else { // other is a FredkinCell
            ptr = new FredkinCell();
        }
    }
    *ptr = *(other.ptr);
}

Cell::~Cell() {
    if (ptr) {
        delete ptr;
        ptr = nullptr;
    }
}
