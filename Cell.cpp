
#include "Cell.hpp"

Cell::Cell(bool isConway) : Cell(isConway, false) { assert(ptr); }

Cell::Cell(bool isConway, bool isAlive) {
    if (isConway) {
        ptr = new ConwayCell(isAlive);
    } else {
        ptr = new FredkinCell(isAlive);
    }
    assert(ptr);
}

Cell::Cell(Cell& rhs) {
    ptr = (rhs.ptr)->clone();
}

Cell::Cell(Cell&& rhs) {
    std::swap((*this).ptr, rhs.ptr);
}

Cell& Cell::operator=(Cell& rhs) {
    if (ptr) {
        delete ptr;
        ptr = nullptr;
    }
    ptr = (rhs.ptr)->clone();
    return *this;
}

Cell& Cell::operator=(Cell&& rhs) {
    Cell that(std::move(rhs));
    std::swap((*this).ptr, that.ptr);
    return *this;
}

int Cell::update (int cardinalNeighbors, int diagonalNeighbors) {
    assert(ptr);
    int result = ptr->update(cardinalNeighbors, diagonalNeighbors);
    if (result == 2) {
        mutate();
    }
    return 0;
}

// only if Life instantiated with Cell and reached the age of 2
void Cell::mutate() {
    assert(ptr);
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