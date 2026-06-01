#include "Position.h"

Position::Position() {
    row = 0;
    col = 0;
}

Position::Position(int row, int col) {
    this->row = row;
    this->col = col;
}

bool Position::equals(const Position& other) const {
    return row == other.row && col == other.col;
}

bool Position::isNeighbour(const Position& other) const {
    int rowDiff = row - other.row;
    int colDiff = col - other.col;

    if (rowDiff < 0) {
        rowDiff = -rowDiff;
    }

    if (colDiff < 0) {
        colDiff = -colDiff;
    }

    return rowDiff + colDiff == 1;
}
