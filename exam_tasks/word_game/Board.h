#ifndef BOARD_H
#define BOARD_H

#include <string>
#include "Cell.h"
#include "Position.h"

using std::string;

class Board {
public:
    static const int SIZE = 5;

private:
    Cell cells[SIZE][SIZE];

public:
    Board();

    void clear();
    bool initStartWord(const string& word);
    bool isInside(const Position& pos) const;
    bool isEmpty(const Position& pos) const;
    bool setLetter(const Position& pos, char ch);
    char getLetter(const Position& pos) const;
    bool hasFilledNeighbour(const Position& pos) const;
    bool isFull() const;
    void print() const;
};

#endif
