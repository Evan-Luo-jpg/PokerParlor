#ifndef DECK_H
#define DECK_H

#include <vector>
#include "card.h"

class Deck
{
private:
    std::vector<Card> cards;

public:
    // Constructor to initialize the deck with 52 cards
    Deck();

    // Function to shuffle the deck
    void shuffle();

    // Function to populate the deck with 52 cards
    void populate();

    // Function to draw a card from the deck
    Card draw();

    // Function to return the number of cards in the deck
    int size() const;

    // Function to reset the deck
    void reset();
};

#endif
