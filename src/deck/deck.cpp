#include "deck.h"
#include <iostream>
#include <algorithm> // For shuffle
#include <random>    // For random number generation
#include "card.h"

// Function to populate the deck with 52 cards
void Deck::populate()
{
    cards.clear();
    for (int suit = HEARTS; suit <= SPADES; suit++)
    {
        for (int rank = TWO; rank <= ACE; rank++)
        {
            cards.push_back(Card(static_cast<Rank>(rank), static_cast<Suit>(suit)));
        }
    }
}

// Constructor to initialize the deck with 52 cards
Deck::Deck()
{
    // Loop through each suit
    populate();
    shuffle();
}

// Function to shuffle the deck
void Deck::shuffle()
{
    // Create a random number generator
    std::random_device rd;
    std::mt19937 g(rd());

    // Shuffle the deck
    std::shuffle(cards.begin(), cards.end(), g);
}

// Function to draw a card from the deck
Card Deck::draw()
{
    // Get the top card from the deck
    if (cards.size() == 0)
    {
        throw std::out_of_range("Cannot draw from an empty deck.");
    }

    Card topCard = cards.back();

    // Remove the top card from the deck
    cards.pop_back();

    return topCard;
}

// Function to return the number of cards in the deck
int Deck::size() const
{
    return cards.size();
}

// Function to reset the deck
void Deck::reset()
{
    // Clear the deck
    populate();
    shuffle();
}