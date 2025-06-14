#include "../game.hpp"

struct EquityResult {
    Player player;
    double equity;
};
EquityResult calcEquity(const Player player, const std::vector<Card> &communityCards,
     Street street, const std::vector<Card> &remainingDeck, int interations);

std::vector<EquityResult> calcEquityAll(
    const std::vector<Player>& players,
    const std::vector<Card>& communityCards,
    Street street,
    const std::vector<Card>& remainingDeck,
    int iterations);



