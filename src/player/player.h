#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "../deck/deck.h"


// Enum to represent the action of a player
enum Action
{
    FOLD,
    CHECK,
    CALL,
    RAISE
};


class Player
{
private:
    std::vector<Card> hand;
    bool folded; // Indicates if the player has folded
    long ID;
    int stack;
    int currentBet;
    bool allIn;
    bool bot;
public:
    // Constructor to initialize the player
    Player(long ID, int stack, bool bot = false);

    // Is all in
    bool isAllIn();

    // Function to reset a player all in
    void resetAllIn();

    // Function to add two cards to the player's hand
    void addCards(Card card1, Card card2);

    // Function to bet a certain amount
    void bet(int amount);

    // Function to add to the player's stack
    void addToStack(int amount);

    // Function to get the player's stack
    int getStack() const;

    // Function to clear the players hand
    void clearHand();

    // Function to reset the player's current bet
    void resetCurrentBet();

    // Function to get the player's current bet
    int getCurrentBet() const;

    // Function to check if the player is still in the hand
    bool hasFolded() const; 

    // Function to fold the player's hand
    void fold();

    // Function to check if the player is a bot
    bool isBot() const
    {
        return bot;
    }

    // Function to turn action to string
    std::string actionToString(Action action) const
    {
        switch (action)
        {
        case FOLD:
            return "Fold";
        case CHECK:
            return "Check";
        case CALL:
            return "Call";
        case RAISE:
            return "Raise";
        default:
            return "Unknown Action";
        }
    }

    //Function to get the action of the player
    Action getAction(std::vector<Action> possibleActions);

    // Function to get the player's ID
    long getID() const;

    // Function to get the player's hand
    std::vector<Card> getHand() const;
};


#endif