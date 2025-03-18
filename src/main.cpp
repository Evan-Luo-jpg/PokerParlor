#include "game.h"
#include <iostream>

int main() {
    Game game(10, 20); // Small blind = 10, Big blind = 20

    // Add players
    game.addPlayer(Player(1, 1000));
    game.addPlayer(Player(2, 1000));
    game.addPlayer(Player(3, 1000));

    // Start a round
    game.startRound();
    game.playRound();
    std::cout << "Game finished." << std::endl;
    return 0;
}
