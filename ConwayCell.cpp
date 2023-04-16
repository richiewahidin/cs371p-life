#include "ConwayCell.hpp"

ConwayCell::ConwayCell(bool alive) : AbstractCell(alive){}

ConwayCell::ConwayCell(ConwayCell& other) : AbstractCell(other._alive){} 

ConwayCell& ConwayCell::operator=(ConwayCell& rhs) = default;

int ConwayCell::update(int cardinalNeighbors, int diagonalNeighbors) {
    int totalNeighbors = cardinalNeighbors + diagonalNeighbors;
    if (_alive && totalNeighbors != 2 && totalNeighbors != 3) {
        _alive = false;
        return -1;
    } else if (!_alive && totalNeighbors == 3) {
        _alive = true;
        return 1;
    }
    return 0;
}

ConwayCell* ConwayCell::clone() {
    return new ConwayCell(*this);
}