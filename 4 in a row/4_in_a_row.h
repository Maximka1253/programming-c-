#ifndef FIELD_H
#define FIELD_H

enum Cell {
    EMPTY = 0,
    RED = 1,
    YELLOW = 2
};

class Field {
public:
    Field(bool isRedFirst);
    void clear(bool isRedFirst);
    bool makeTurn(int column);
    bool isWon(bool red) const;
    bool isOver() const;
    Cell getCell(int i, int j) const;
    bool isRedTurnNow() const;
    void print() const;
    void printResult() const;

private:
    static const int FIELD_WIDTH = 7;
    static const int FIELD_HEIGHT = 6;
    Cell cells[FIELD_WIDTH][FIELD_HEIGHT];
    bool isRedTurn;
    Cell winner;

    void checkWinner();
};

#endif