#include "game.hpp"
#include <iostream>

int main() {
    Game game(10, 20); // Small blind = 10, Big blind = 20

    // Add players
    game.addPlayer(Player(0, 100, true)); // Just for testing right now
    game.addPlayer(Player(1, 100, true)); // Bot player
    game.addPlayer(Player(2, 100, true)); // Bot player
    game.addPlayer(Player(3, 100, true)); // Bot player
    game.addPlayer(Player(4, 100, true)); // Bot player


    // Start a round
    game.startRound();
    game.playRound();
    std::cout << "Game finished." << std::endl;
    return 0;
}
