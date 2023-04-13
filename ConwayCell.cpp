#include "ConwayCell.hpp"

ConwayCell::ConwayCell(bool alive) : AbstractCell(alive){ }

ConwayCell& ConwayCell::operator=(ConwayCell& rhs) = default;

bool ConwayCell::update(int n_neighbors) {
    if (_alive && n_neighbors != 2 && n_neighbors != 3) {
        _alive = false;
    } else if (!_alive && n_neighbors == 3) {
        _alive = true;
    }
    return false;
}