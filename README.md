﻿# PokerParlor

A sophisticated Texas Hold'em poker engine written in C++ featuring advanced hand evaluation, equity calculation, and intelligent bot players.

## Overview

PokerParlor is a complete poker simulation engine that implements Texas Hold'em rules with the following key features:

- **Fast Hand Evaluator**: Optimized 7-card hand evaluation using lookup tables
- **Equity Calculator**: Monte Carlo simulation for calculating hand equity
- **Intelligent Bots**: AI players that make decisions based on equity and pot odds
- **Complete Game Engine**: Full poker game flow from preflop to showdown

## Project Structure

```
src/
├── main.cpp              # Main entry point and game setup
├── game.cpp              # Core game logic and flow control
├── game.hpp              # Game class interface
├── deck/                 # Card and deck management
│   ├── card.hpp/cpp      # Card representation and utilities
│   └── deck.hpp/cpp      # Deck shuffling and card dealing
├── evaluator/            # Hand evaluation system
│   ├── evaluator.hpp/cpp # Fast 7-card hand evaluator
│   ├── arrays.h          # Lookup tables for hand ranking
│   └── tester.cpp        # Evaluation testing utilities
├── equity/               # Equity calculation system
│   ├── equity.hpp/cpp    # Monte Carlo equity simulation
└── player/               # Player management and AI
    ├── player.hpp/cpp    # Player class with bot decision logic
```

## Key Components

### Hand Evaluator

The hand evaluator is based on the [Suffecool 7-card evaluator](https://github.com/suffeCool/poker), which uses lookup tables for extremely fast hand ranking. The evaluator can determine the best 5-card hand from 7 cards in constant time.

**Features:**
- Evaluates all standard poker hands (High Card to Royal Flush)
- Uses bit manipulation for optimal performance
- Supports both 5-card and 7-card hand evaluation
- Includes comprehensive lookup tables for instant hand ranking

**Usage:**
```cpp
int* hand = encodeDeck(playerCards + communityCards);
unsigned short score = eval_7hand(hand);
// Lower scores indicate better hands
```

### Equity Calculator

The equity system uses Monte Carlo simulation to calculate the probability of winning for each player at any point in the hand.

**Features:**
- Monte Carlo simulation with configurable iterations (default: 1000)
- Calculates both win percentage and tie percentage
- Updates equity after each street (preflop, flop, turn, river)
- Handles all-in situations and side pots

**Algorithm:**
1. Shuffle remaining deck cards
2. Complete the board with random cards
3. Evaluate all players' hands
4. Determine winner(s) and update statistics
5. Repeat for specified number of iterations

**Usage:**
```cpp
std::vector<EquityResult> results = calcEquityAll(
    players, communityCards, street, remainingDeck, iterations, deckSize
);
```

### Bot Decision Making

The AI players make decisions based on equity calculations and pot odds analysis.

**Decision Logic:**
- **Call/Fold Decision**: Compares equity vs pot odds
  - If `equity > pot_odds`, the bot calls (positive expected value)
  - Otherwise, the bot folds
- **Raise Decision**: Raises when equity > 0.4 (40%)
- **Check Decision**: Checks when no better action is available

**Pot Odds Calculation:**
```cpp
double potOdds = callAmount / (pot + callAmount);
```

**Bot Behavior:**
- Makes mathematically sound decisions based on equity
- Considers stack sizes and betting amounts
- Adapts strategy based on current street and board texture

## Building the Project

### Prerequisites
- CMake 3.28.3 or higher
- C++23 compatible compiler
- Linux/WSL environment

### Build Instructions

```bash
# Clone the repository
git clone <repository-url>
cd PokerParlor

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run the program
./poker_bot
```

### Debug Build

The project includes sanitizers for debugging:
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
make
```

## Game Flow

1. **Game Initialization**: Set up players, blinds, and deck
2. **Preflop**: Deal hole cards, post blinds, betting round
3. **Flop**: Deal 3 community cards, betting round
4. **Turn**: Deal 1 community card, betting round
5. **River**: Deal final community card, betting round
6. **Showdown**: Evaluate hands and determine winner

## Example Usage

```cpp
#include "game.hpp"

int main() {
    // Create game with 10/20 blinds
    Game game(10, 20);
    
    // Add players (human and bots)
    game.addPlayer(Player(0, 100, false));  // Human player
    game.addPlayer(Player(1, 100, true));   // Bot player
    game.addPlayer(Player(2, 100, true));   // Bot player
    
    // Start and play a round
    game.startRound();
    game.playRound();
    
    return 0;
}
```

## Technical Details

### Hand Encoding

Cards are encoded using a bit-based system:
- **Rank**: 4 bits (2-14 for 2-Ace)
- **Suit**: 4 bits (hearts, diamonds, clubs, spades)
- **Prime**: Used for hand evaluation lookup
- **Bit flags**: Additional metadata for evaluation

### Performance Optimizations

- **Lookup Tables**: Pre-computed hand rankings for instant evaluation
- **Bit Manipulation**: Efficient card encoding and comparison
- **Monte Carlo**: Parallelizable equity calculation
- **Memory Management**: Proper cleanup of dynamically allocated arrays

### Game State Management

The game maintains state for:
- Current street (preflop, flop, turn, river, showdown)
- Player positions and button
- Pot size and current bets
- Community cards
- Equity calculations

## Future Enhancements

- **Multi-threading**: Parallel equity calculations
- **Advanced Bot Strategies**: Position-based play, opponent modeling
- **Tournament Support**: Multi-table tournaments
- **Web Interface**: Real-time game visualization
- **Hand History**: Detailed logging and analysis
- **Machine Learning**: Neural network-based decision making

## Contributing

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Add tests if applicable
5. Submit a pull request


## Acknowledgments

- Hand evaluator based on Suffecool's 7-card evaluator
- Monte Carlo equity calculation inspired by poker theory
- C++23 features for modern development practices
