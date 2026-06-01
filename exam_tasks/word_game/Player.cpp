#include "Player.h"

Player::Player() {
    name = "Player";
    score = 0;
}

Player::Player(const string& name) {
    this->name = name;
    score = 0;
}

string Player::getName() const {
    return name;
}

int Player::getScore() const {
    return score;
}

void Player::addScore(int points) {
    score += points;
}
