#include "Cell.h"

Cell::Cell() {
    clear();
}

bool Cell::isEmpty() const {
    return empty;
}

char Cell::getLetter() const {
    return letter;
}

void Cell::setLetter(char ch) {
    letter = ch;
    empty = false;
}

void Cell::clear() {
    letter = ' ';
    empty = true;
}
