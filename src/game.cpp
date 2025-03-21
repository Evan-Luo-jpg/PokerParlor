#include "game.h"
#include <iostream>

// Constructor to initialize the game
Game::Game(int smallBlind, int bigBlind) : pot(0), currentPlayerIndex(0), street(PREFLOP), highestBet(0), playersInHand(0), smallBlind(smallBlind), bigBlind(bigBlind), currentButtonIndex(0) {}

// Add a player to the game
void Game::addPlayer(Player player)
{
    players.push_back(player);
}

// Start a new round
void Game::startRound()
{
    deck.reset();
    deck.shuffle();
    pot = 0;
    highestBet = 0;
    playersInHand = players.size();
    currentButtonIndex = (currentButtonIndex + 1) % players.size();
    street = PREFLOP;

    // Deal two cards to each player
    for (auto &player : players)
    {
        player.clearHand();
        player.addCards(deck.draw(), deck.draw());
    }
    std::cout << "Players have been dealt their cards.\n";

    // Post blinds
    int smallBlindIndex = (currentButtonIndex + 1) % players.size();
    int bigBlindIndex = (smallBlindIndex + 1) % players.size();

    players[smallBlindIndex].bet(smallBlind);
    players[bigBlindIndex].bet(bigBlind);
    pot += smallBlind + bigBlind;
    highestBet = bigBlind;
    std::cout << "Player " << players[smallBlindIndex].getID() << " posts the small blind of " << smallBlind << ".\n";
    std::cout << "Player " << players[bigBlindIndex].getID() << " posts the big blind of " << bigBlind << ".\n";

    currentPlayerIndex = (bigBlindIndex + 1) % players.size();
}

// Play a round with betting logic
void Game::playRound()
{
    while (playersInHand > 1 && street != SHOWDOWN)
    {
        // Print street
        std::cout << "The current street is: " << street << "\n";

        playStreet();
        if (playersInHand == 1)
        {
            // Award the pot to the last remaining player
            for (auto &player : players)
            {
                if (!player.hasFolded())
                {
                    player.addToStack(pot);
                    std::cout << "Player " << player.getID() << " wins the pot of " << pot << " chips!\n";
                    return;
                }
            }
        }

        if (playersAllIn())
        {
            evaluateWinner();
            return;
        }
        // Move to the next street
        street = static_cast<Street>(street + 1);
    }

    // If the game reaches showdown, evaluate the winner
    if (street == SHOWDOWN)
    {
        evaluateWinner();
        return;
    }
}

void Game::playStreet()
{
    bool bettingOver = false;
    int lastRaiser = -1;
    bool bigBlindActed = false;
    int smallBlindIndex = (currentButtonIndex + 1) % players.size();
    int bigBlindIndex = (smallBlindIndex + 1) % players.size();
    currentPlayerIndex = getFirstToActIndex();

    while (!bettingOver)
    {
        Player &player = getCurrentPlayer();

        if (player.hasFolded())
        {
            nextPlayer();
            continue;
        }

        if (player.getStack() <= 0 && player.isAllIn() == false)
        {
            player.fold();
            playersInHand--;
            nextPlayer();
            continue;
        }

        std::vector<Action> possibleActions;
        if (player.getCurrentBet() < highestBet)
        {
            possibleActions = {FOLD, CALL, RAISE};
        }
        else
        {
            possibleActions = {FOLD, CHECK, RAISE};
        }

        Action action = player.getAction(possibleActions);
        switch (action)
        {
        case CHECK:
            std::cout << "Player " << player.getID() << " checks.\n";
            break;

        case FOLD:
            player.fold();
            playersInHand--;
            std::cout << "Player " << player.getID() << " folds.\n";
            break;

        case CALL:
        {
            int callAmount = highestBet - player.getCurrentBet();
            player.bet(callAmount);
            pot += callAmount;
            std::cout << "Player " << player.getID() << " calls.\n";
            break;
        }

        case RAISE:
        {
            int raiseAmount;
            std::cout << "Player " << player.getID() << " raises by: ";
            std::cin >> raiseAmount;
            highestBet += raiseAmount;
            lastRaiser = currentPlayerIndex;
            player.bet(highestBet);
            pot += highestBet;
            std::cout << "Player " << player.getID() << " raises to " << highestBet << ".\n";
            break;
        }
        }
        nextPlayer();

        // Ensure big blind gets a final action pre-flop if no raise occurred after their blind
        if (street == PREFLOP && !bigBlindActed && currentPlayerIndex == bigBlindIndex)
        {
            bigBlindActed = true;
            continue;
        }
        if (lastRaiser == -1 && currentPlayerIndex != getFirstToActIndex())
        {
            // AKA the player just checked and it is not back on the first to act yet
            continue;
        }

        bettingOver = bettingComplete(lastRaiser);
    }
}

// Check if the betting round is complete
bool Game::bettingComplete(int lastRaiser)
{
    int playersCalled = 0;
    for (auto &player : players)
    {
        if (!player.hasFolded() && player.getCurrentBet() == highestBet)
        {
            playersCalled++;
        }
    }

    return playersInHand == 1 || playersCalled == playersInHand;
}

// Move to the next player
void Game::nextPlayer()
{
    do
    {
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    } while (players[currentPlayerIndex].hasFolded());
}

// Get the current player
Player &Game::getCurrentPlayer()
{
    return players[currentPlayerIndex];
}

// Evaluate winner (placeholder)
void Game::evaluateWinner()
{
    std::cout << "Evaluating winner... (logic to be implemented)\n";

    // Debugging and print each players hand and stats
}

// Get the current street
Street Game::getStreet()
{
    return street;
}

// Check if all players are all in
bool Game::playersAllIn()
{
    int playersAllIn = 0;
    for (auto &player : players)
    {
        if (player.isAllIn())
        {
            playersAllIn++;
        }
    }
    return playersAllIn == playersInHand;
}

int Game::getFirstToActIndex()
{
    int smallBlindIndex = (currentButtonIndex + 1) % players.size();
    int bigBlindIndex = (smallBlindIndex + 1) % players.size();
    int firstToAct = (currentButtonIndex + 1) % players.size();
    if (street == PREFLOP)
    {
        firstToAct = (bigBlind + 2) % players.size();
    }

    // Find the first player still in the hand
    while (players[firstToAct].hasFolded())
    {
        firstToAct = (firstToAct + 1) % players.size();
    }

    return firstToAct;
}
