#include <clocale>
#include "Game.h"

int main() {
    
    Game game;
    if (game.init()) {
        game.play();
    }

    return 0;
}
