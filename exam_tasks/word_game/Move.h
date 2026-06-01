#ifndef MOVE_H
#define MOVE_H

#include <string>
#include "Position.h"

using std::string;

class Move {
public:
    bool pass;
    char addedLetter;
    Position addedPosition;
    string word;

    Move() {
        pass = false;
        addedLetter = ' ';
        addedPosition = Position();
        word = "";
    }
};

#endif
