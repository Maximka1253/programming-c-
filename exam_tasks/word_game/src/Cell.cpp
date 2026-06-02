#include "Cell.h"

Cell::Cell() {
    clear();
}

bool Cell::isEmpty() const {
    return empty;
}

string Cell::getLetter() const {
    return letter;
}

void Cell::setLetter(const string& value) {
    letter = value;
    empty = false;
}

void Cell::clear() {
    letter = "";
    empty = true;
}
