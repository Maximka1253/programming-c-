#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>
#include <vector>
#include "Move.h"
#include "Player.h"

using std::ofstream;
using std::string;
using std::vector;

class Logger {
private:
    ofstream file;

public:
    bool open(const string& filename);
    void write(const string& message);
    void logStart(const vector<Player>& players, const string& startWord);
    void logMove(const Player& player, const Move& move, const string& result);
    void logEnd(const vector<Player>& players, const string& result);
};

#endif
