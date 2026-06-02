#include "Board.h"
#include "RussianText.h"
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
    vector<string> letters = RussianText::splitRussianLetters(word);
    if (static_cast<int>(letters.size()) != SIZE) {
        return false;
    }

    // Ставим стартовое слово в центр поля.
    clear();

    int row = SIZE / 2;
    for (int col = 0; col < SIZE; col++) {
        cells[row][col].setLetter(letters[col]);
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
// Ставим букву на доску. Возвращаем true, если успешно.
bool Board::setLetter(const Position& pos, const string& letter) {
    if (!isInside(pos) || !isEmpty(pos)) {
        return false;
    }

    if (!RussianText::isSingleRussianLetter(letter)) {
        return false;
    }

    cells[pos.row][pos.col].setLetter(RussianText::normalizeRussianWord(letter));
    return true;
}
// Получаем букву с доски. Если позиция некорректная, возвращаем пустую строку.
string Board::getLetter(const Position& pos) const {
    if (!isInside(pos)) {
        return "";
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
