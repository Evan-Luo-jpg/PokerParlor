#include <vector>
#include "player/player.hpp"
#include <iostream>
#include "../equity/equity.hpp"
#include "../evaluator/evaluator.hpp"




class Game{
    private:
    int time;
    int smallBlind;
    int bigBlind;
    Street street;
    int highestBet;
    int pot;
    int currentButtonIndex;
    int currentPlayerIndex;
    int playersInHand;
    std::vector<Player> players;
    Deck deck;

    std::vector<Card> communityCards;

    std::vector<EquityResult> equityResults;

    public:
    // Constructor to initialize the game
    Game(int smallBlind, int bigBlind);


    // Function to add a player to the game
    void addPlayer(Player player);

    // Function to start the game
    void startRound();

    // Function to play a round
    void playRound();

    // Function to evaluate the winner
    void evaluateWinner();

    // Function to get the current street
    Street getStreet();

    // Function to check if the betting is complete
    bool bettingComplete(int player_index);

    // Find the player first to act
    int getFirstToActIndex();

    // Get community cards
    std::vector<Card> getCommunityCards() {
        return communityCards;
    }

    // Helpers
    // Function to play the street
    void playStreet();
    void nextPlayer();
    bool playersAllIn();
    Player& getCurrentPlayer();

};