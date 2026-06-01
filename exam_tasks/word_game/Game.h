#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include "Board.h"
#include "Dictionary.h"
#include "Logger.h"
#include "Player.h"
#include "WordValidator.h"

using std::string;
using std::vector;

class Game {
private:
    Board board;
    vector<Player> players;
    Dictionary dictionary;
    WordValidator validator;
    Logger logger;
    vector<string> usedWords;
    int currentPlayer;
    int passesInRow;

    bool hasPossibleMove() const;
    bool isWordUsed(const string& word) const;

public:
    Game();

    bool init();
    void play();
    Move inputMove();
    void nextPlayer();
    bool isGameOver() const;
    void printResults() const;
    string getWinnerText() const;
};

#endif
