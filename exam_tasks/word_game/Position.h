#ifndef POSITION_H
#define POSITION_H

class Position {
public:
    int row;
    int col;

    Position();
    Position(int row, int col);

    bool equals(const Position& other) const;
    bool isNeighbour(const Position& other) const;
};

#endif
