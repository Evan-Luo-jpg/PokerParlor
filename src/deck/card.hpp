#ifndef CARD_H
#define CARD_H

#include <string>

// Enum to represent the suit of a card
enum Suit
{
    HEARTS,
    DIAMONDS,
    CLUBS,
    SPADES
};

// Enum to represent the rank of a card
enum Rank
{
    TWO = 2,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};

// Card class declaration
class Card{
    private:
        Rank rank;
        Suit suit;

    public:
        // Constructor to initialize the card
        Card(Rank rank, Suit suit);

        // Function to return a string representation of the card
        std::string toString() const;

        // Getters for rank and suit
        Rank getRank() const;
        Suit getSuit() const;
};

#endif
