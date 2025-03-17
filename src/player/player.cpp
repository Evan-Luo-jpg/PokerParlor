#include "player.h"
#include <iostream>
#include "deck/card.h"
#include "deck/deck.h"


// Constructor to initialize the player
Player::Player(long ID, int stack)
{
    this->ID = ID;
    this->stack = stack;
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
Action Player::getAction()
{
    // Will want to implement user action as well as what actions are currently available
    // For now, the player will always fold
    return FOLD;
}

// Function to get the player's ID
long Player::getID() const
{
    return ID;
}

// Function to get the player's hand
std::vector<Card> Player::getHand() const
{
    return hand;
}