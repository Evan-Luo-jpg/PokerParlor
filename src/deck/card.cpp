#include "card.hpp"
#include <sstream> // For stringstream

// Constructor
Card ::Card(Rank rank, Suit suit){
    this->rank = rank;
    this->suit = suit;
}

// Convert card to a readable string
std::string Card::toString() const {
    std::stringstream ss;
    std::string rankStr;
    std::string suitStr;

    // Map rank to string
    switch (rank) {
        case TWO: rankStr = "2"; break;
        case THREE: rankStr = "3"; break;
        case FOUR: rankStr = "4"; break;
        case FIVE: rankStr = "5"; break;
        case SIX: rankStr = "6"; break;
        case SEVEN: rankStr = "7"; break;
        case EIGHT: rankStr = "8"; break;
        case NINE: rankStr = "9"; break;
        case TEN: rankStr = "10"; break;
        case JACK: rankStr = "JACK"; break;
        case QUEEN: rankStr = "QUEEN"; break;
        case KING: rankStr = "KING"; break;
        case ACE: rankStr = "ACE"; break;
    }

    // Map suit to string
    switch (suit) {
        case HEARTS: suitStr = "Hearts"; break;
        case DIAMONDS: suitStr = "Diamonds"; break;
        case CLUBS: suitStr = "Clubs"; break;
        case SPADES: suitStr = "Spades"; break;
    }

    ss << rankStr << " of " << suitStr;
    return ss.str();
}

// Getters
Rank Card::getRank() const {
    return rank;
}

Suit Card::getSuit() const {
    return suit;
}
