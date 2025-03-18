#include "game.h"
#include <iostream>

Game::Game() : pot(0), currentPlayerIndex(0), street(PREFLOP),  {}

// Add a player to the game
void Game::addPlayer(Player player) {
    players.push_back(player);
}

// Start a new round
void Game::startRound() {
    deck.reset();
    deck.shuffle();
    pot = 0;
    playersInHand = players.size();    
    // Deal two cards to each player
    for (auto& player : players) {
        player.clearHand();
        player.addCards(deck.draw(), deck.draw());
    }

    std::cout << "Round started. Players have been dealt their cards.\n";
}

// Play a round (simplified)
void Game::playRound() {
    while(bettingComplete()){

    }
}

//Checks if betting is complete
bool Game::bettingComplete(){
    if(getCurrentPlayer().() == 0){
        return true;
    }
}

// Move to the next player
void Game::nextPlayer() {
    currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
}

// Get the current player
Player& Game::getCurrentPlayer() {
    return players[currentPlayerIndex];
}

// Evaluate winner (placeholder)
void Game::evaluateWinner() {
    std::cout << "Evaluating winner... (logic to be implemented)\n";
}
