#include "player.hpp"
#include <iostream>
#include <chrono>


// Constructor to initialize the player
Player::Player(long ID, int stack, bool bot)
{
    this->ID = ID;
    this->stack = stack;
    currentBet = 0;
    allIn = false;
    this->bot = bot; // Set to true if the player is a bot
}

// Function to reset the player
void Player::reset()
{
    allIn = false;
    currentBet = 0;
    hand.clear();
}

// Is all in
bool Player::isAllIn()
{
    return allIn;
}

// Function to reset a player all in
void Player::resetAllIn()
{
    allIn = false;
}

// Function to add two cards to the player's hand
void Player::addCards(Card card1, Card card2)
{
    hand.push_back(card1);
    hand.push_back(card2);
}

// Function to bet a certain amount
void Player::bet(int amount)
{
    if (amount >= stack)
    {
        std::cout << "Player " << ID << " is all in with " << stack << " chips.\n";
        amount = stack;
        allIn = true;
    }
    currentBet += amount;
    stack -= amount;
}

// Function to add to the player's stack
void Player::addToStack(int amount)
{
    stack += amount;
}

// Function to get the player's stack
int Player::getStack() const
{
    return stack;
}

// Function to clear the players hand
void Player::clearHand()
{
    hand.clear();
}

//Function to get the action of the player
Action Player::getAction(std::vector<Action> possibleActions)
{
    //Choose from the possible actions

    // If the timer reaches 60, the player will fold
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    while (elapsed.count() < 60)
    {
        end = std::chrono::high_resolution_clock::now();

        // If the player is not a bot, get the action from the console
        std::cout << "Player " << ID << " has " << stack << " chips. Choose an action: ";
        
        //Get player action from console
        for (size_t i = 0; i < possibleActions.size(); ++i)
        {
            std::cout << i + 1 << ":" << actionToString(possibleActions[i]) << " ";
        }
        std::cout << "\n";
        std::cout << "Enter action number: ";
        int actionNumber;
        std::cin >> actionNumber;
        if (actionNumber < 1 || actionNumber > possibleActions.size())
        {
            std::cout << "Invalid action. Please try again.\n";
            continue;
        }


        elapsed = end - start;


        return possibleActions[actionNumber - 1];
    }
    // Will want to implement user action as well as what actions are currently available
    // For now, the player will always fold
    return FOLD;
}


//Overloaded getAction function for bots
Action Player::getAction(std::vector<Action> possibleActions, double equity, int pot, int callAmount, int stack)
{
    if (bot) {
        // Calculate pot odds
        double potOdds = (double)callAmount / (pot + callAmount);

        // Only call if equity > pot odds (positive EV)
        if (std::find(possibleActions.begin(), possibleActions.end(), CALL) != possibleActions.end()) {
            if (equity > potOdds) {
                return CALL;
            } else {
                return FOLD;
            }
        }
        // Raise logic: raise only if equity is greater than 0.4
        if (equity > 0.4) {
           return RAISE;
        }
        // Otherwise, check if possible
        if (std::find(possibleActions.begin(), possibleActions.end(), CHECK) != possibleActions.end()) {
            return CHECK;
        }
    }

    // If the player is not a bot or if nothing is possible
    return FOLD;
}

// Function to get the player's ID
long Player::getID() const
{
    return ID;
}

// Function to fold the player's hand
void Player::fold()
{
    clearHand();
}

// Function to reset the players current bet
void Player::resetCurrentBet()
{
    currentBet = 0;
}

// Function to get the player's current bet
int Player::getCurrentBet() const
{
    return currentBet;
}

// Function to check if the player is still in the hand
bool Player::hasFolded() const
{
    return hand.empty();
}

// Function to get the player's hand
std::vector<Card> Player::getHand() const
{
    return hand;
}