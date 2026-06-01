#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using std::string;

class Player {
private:
    string name;
    int score;

public:
    Player();
    Player(const string& name);

    string getName() const;
    int getScore() const;
    void addScore(int points);
};

#endif
