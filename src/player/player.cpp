#include "player.h"
#include <iostream>
#include <chrono>


// Constructor to initialize the player
Player::Player(long ID, int stack)
{
    this->ID = ID;
    this->stack = stack;
    currentBet = 0;
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
    currentBet += amount;
    stack -= amount;
}

// Function to add to the player's stack
void Player::addToStack(int amount)
{
    stack += amount;
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

    // If the timer reaches 30, the player will fold
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    while (elapsed.count() < 30)
    {
        end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;

        // In here the player will choose an action
    }
    // Will want to implement user action as well as what actions are currently available
    // For now, the player will always fold
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