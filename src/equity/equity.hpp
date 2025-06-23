#include "../evaluator/evaluator.hpp"
#include "../deck/deck.hpp"
#include "../player/player.hpp"
#include <vector>
#include <cstring>
#include <sstream>
struct EquityResult {
    Player player;
    double equity;
    double tie;
};

enum Street{
    PREFLOP,
    FLOP,
    TURN,
    RIVER,
    SHOWDOWN
};

EquityResult calcEquity(const std::vector<Player>& players, const Player player, const int* communityCards,
     Street street, const int* remainingDeck, int interations, int sizeofDeck);

std::vector<EquityResult> calcEquityAll(
    const std::vector<Player>& players,
    const int* communityCards,
    Street street,
    const int* remainingDeck,
    int iterations, int sizeofDeck);

std::string equityToString(const EquityResult& result);

std::string equityResultsToString(const std::vector<EquityResult>& results);


