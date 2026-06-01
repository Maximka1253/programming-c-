#include "Board.h"
#include <cctype>
#include <iostream>

using namespace std;

Board::Board() {
    clear();
}

void Board::clear() {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            cells[row][col].clear();
        }
    }
}

bool Board::initStartWord(const string& word) {
    if (word.length() != SIZE) {
        return false;
    }

    // Ставим стартовое слово в центр поля.
    clear();

    int row = SIZE / 2;
    for (int col = 0; col < SIZE; col++) {
        char ch = static_cast<char>(tolower(static_cast<unsigned char>(word[col])));
        cells[row][col].setLetter(ch);
    }

    return true;
}

bool Board::isInside(const Position& pos) const {
    return pos.row >= 0 && pos.row < SIZE && pos.col >= 0 && pos.col < SIZE;
}

bool Board::isEmpty(const Position& pos) const {
    if (!isInside(pos)) {
        return false;
    }

    return cells[pos.row][pos.col].isEmpty();
}

bool Board::setLetter(const Position& pos, char ch) {
    if (!isInside(pos) || !isEmpty(pos)) {
        return false;
    }

    ch = static_cast<char>(tolower(static_cast<unsigned char>(ch)));
    cells[pos.row][pos.col].setLetter(ch);
    return true;
}

char Board::getLetter(const Position& pos) const {
    if (!isInside(pos)) {
        return ' ';
    }

    return cells[pos.row][pos.col].getLetter();
}

bool Board::hasFilledNeighbour(const Position& pos) const {
    // Проверяем соседей по вертикали и горизонтали.
    Position neighbours[4] = {
        Position(pos.row - 1, pos.col),
        Position(pos.row + 1, pos.col),
        Position(pos.row, pos.col - 1),
        Position(pos.row, pos.col + 1)
    };

    for (int i = 0; i < 4; i++) {
        if (isInside(neighbours[i]) && !isEmpty(neighbours[i])) {
            return true;
        }
    }

    return false;
}

bool Board::isFull() const {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (cells[row][col].isEmpty()) {
                return false;
            }
        }
    }

    return true;
}

void Board::print() const {
    cout << "\nИгровое поле:\n";
    cout << "   ";
    for (int col = 0; col < SIZE; col++) {
        cout << col << " ";
    }
    cout << "\n";

    for (int row = 0; row < SIZE; row++) {
        cout << row << "  ";
        for (int col = 0; col < SIZE; col++) {
            if (cells[row][col].isEmpty()) {
                cout << ". ";
            } else {
                cout << cells[row][col].getLetter() << " ";
            }
        }
        cout << "\n";
    }
}
