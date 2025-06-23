#include "equity.hpp"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cstring>
#include <unordered_map>

EquityResult calcEquity(const std::vector<Player>& players, const Player player,
                        const int* communityCards, Street street,
                        const int* remainingDeck, int iterations, int sizeofDeck) {
    int knownBoardSize = 0;
    switch (street) {
        case PREFLOP: knownBoardSize = 0; break;
        case FLOP:    knownBoardSize = 3; break;
        case TURN:    knownBoardSize = 4; break;
        case RIVER:   knownBoardSize = 5; break;
        default: break;
    }

    int wins = 0, ties = 0;
    std::srand(std::time(nullptr)); // only seed once

    for (int iter = 0; iter < iterations; ++iter) {
        // 1. Copy and shuffle only the valid part of the deck
        int deckCopy[sizeofDeck];
        std::memcpy(deckCopy, remainingDeck, sizeof(int) * sizeofDeck);
        std::random_shuffle(deckCopy, deckCopy + sizeofDeck);

        // 2. Complete the board
        int fullBoard[5];
        std::memcpy(fullBoard, communityCards, knownBoardSize * sizeof(int));
        int needed = 5 - knownBoardSize;
        for (int j = 0; j < needed; ++j) {
            fullBoard[knownBoardSize + j] = deckCopy[j];  // use only the top of the shuffled portion
        }

        // 3. Evaluate hands
        std::unordered_map<long, unsigned short> scores;
        unsigned short bestScore = 9999;
        std::vector<long> winners;

        for (const auto& p : players) {
            if (p.hasFolded()) continue;

            int fullHand[7];
            auto h = p.getHand();
            fullHand[0] = encodeCard(h[0]);
            fullHand[1] = encodeCard(h[1]);
            std::memcpy(fullHand + 2, fullBoard, sizeof(int) * 5);

            unsigned short score = eval_7hand(fullHand);
            scores[p.getID()] = score;

            if (score < bestScore) {
                bestScore = score;
                winners.clear();
                winners.push_back(p.getID());
            } else if (score == bestScore) {
                winners.push_back(p.getID());
            }
        }

        // 4. Update equity stats for your player
        for (auto id : winners) {
            if (id == player.getID()) {
                if (winners.size() == 1) wins++;
                else ties++;
            }
        }
    }

    double winRate = (double)wins / iterations;
    double tieRate = (double)ties / iterations;

    return EquityResult{player, winRate, tieRate};
}

std::vector<EquityResult> calcEquityAll(
    const std::vector<Player>& players,
    const int* communityCards,
    Street street,
    const int* remainingDeck,
    int iterations, int sizeofDeck) {
    
    std::vector<EquityResult> results;
    for (const auto& player : players) {
        results.push_back(calcEquity(players, player, communityCards, street, remainingDeck, iterations, sizeofDeck));
    }
    return results;
}

