#include "Cell.hpp"

// Change from live Fredkin Cell to Live Conway Cell
void Cell::mutate() {
    assert(ptr);
    // Delete the fredkin cell
    delete ptr;
    // Create a new conway cell
    ptr = new ConwayCell(true);
}

Cell::Cell() : Cell::Cell(false) { }

Cell::Cell(bool alive) { ptr = new FredkinCell(alive); }

Cell::Cell(const Cell& rhs) {
    ptr = (rhs.ptr)->clone();
}

Cell& Cell::operator=(Cell& rhs) {
    if (ptr) {
        delete ptr;
        ptr = nullptr;
    }
    ptr = (rhs.ptr)->clone();
    return *this;
}

int Cell::update (int cardinalNeighbors, int diagonalNeighbors) {
    assert(ptr);
    int result = ptr->update(cardinalNeighbors, diagonalNeighbors);
    if (result == 2) {
        mutate();
        return 0;
    }
    return result;
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