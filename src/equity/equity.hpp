#include "../game.cpp"
#include <cstring>
#include <sstream>
struct EquityResult {
    Player player;
    double equity;
    double tie;
};
EquityResult calcEquity(const std::vector<Player>& players, const Player player, const int* communityCards,
     Street street, const int* remainingDeck, int interations, int sizeofDeck);

std::vector<EquityResult> calcEquityAll(
    const std::vector<Player>& players,
    const int* communityCards,
    Street street,
    const int* remainingDeck,
    int iterations, int sizeofDeck);

std::string equityToString(const EquityResult& result) {
    std::stringstream ss;
    ss << "Player ID: " << result.player.getID() << ", Equity: " << result.equity
       << ", Tie: " << result.tie;
    return ss.str();
}

std::string equityResultsToString(const std::vector<EquityResult>& results) {
    std::stringstream ss;
    for (const auto& result : results) {
        ss << equityToString(result) << "\n";
    }
    return ss.str();
}


