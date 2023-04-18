#include "ConwayCell.hpp"

ostream& ConwayCell::write (ostream& out) const {
    char symbol = _alive ? '*' : '.';
    return out << symbol;
};

ConwayCell::ConwayCell(bool alive) : AbstractCell(alive){}

int ConwayCell::update(int cardinalNeighbors, int diagonalNeighbors) {

    // Conway cells look at both cardinal and diagonal neighbors
    int totalNeighbors = cardinalNeighbors + diagonalNeighbors;
    assert(totalNeighbors >= 0);

    // Live cell dies
    if (_alive && totalNeighbors != 2 && totalNeighbors != 3) {
        _alive = false;
        return -1;

    // Dead cell becomes alive
    } else if (!_alive && totalNeighbors == 3) {
        _alive = true;
        return 1;
    }

    // Either live cell remains alive or dead cell remains dead
    return 0;
}

ConwayCell* ConwayCell::clone() {
    return new ConwayCell(*this);
}