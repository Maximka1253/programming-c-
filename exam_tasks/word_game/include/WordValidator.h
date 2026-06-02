#ifndef WORD_VALIDATOR_H
#define WORD_VALIDATOR_H

#include <string>
#include <vector>
#include "Board.h"
#include "Dictionary.h"
#include "Move.h"

using std::string;
using std::vector;

class WordValidator {
public:
    bool validateMove(
        const Board& board,
        const Move& move,
        const Dictionary& dictionary,
        const vector<string>& usedWords,
        string& errorMessage
    ) const;
};

#endif
