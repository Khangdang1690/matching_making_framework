#include "Match.h"

// Constructor: stores match ID, players, and average MMR
Match::Match(int id, std::vector<std::shared_ptr<Player>> players, int avgMmr)
    : m_matchId(id), m_players(std::move(players)), m_averageMmr(avgMmr) {}

// Virtual destructor
Match::~Match() {}

// Returns the match ID
int Match::getMatchId() const { return m_matchId; }

// Returns the average MMR of all players in this match
int Match::getAverageMmr() const { return m_averageMmr; }

// Returns the list of players in this match
const std::vector<std::shared_ptr<Player>>& Match::getPlayers() const {
    return m_players;
}

// Displays a normal match: match ID, average MMR, and each player
void Match::display(std::ostream& os) const {
    os << "--- Normal Match #" << m_matchId
       << " (Avg MMR: " << m_averageMmr << ") ---\n";
    for (const auto& p : m_players) {
        os << "  " << *p << "\n";
    }
}
