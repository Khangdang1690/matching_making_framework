#include "RankedMatch.h"

// Constructor: creates a ranked match and picks the highest-MMR player as winner
RankedMatch::RankedMatch(int id, std::vector<std::shared_ptr<Player>> players, int avgMmr)
    : Match(id, std::move(players), avgMmr), m_winnerIndex(0)
{
    // Determine the winner: player with the highest MMR
    for (int i = 1; i < static_cast<int>(m_players.size()); ++i) {
        if (m_players[i]->getMmr() > m_players[m_winnerIndex]->getMmr()) {
            m_winnerIndex = i;
        }
    }
}

// Destructor override
RankedMatch::~RankedMatch() {}

// Returns a pointer to the winning player
std::shared_ptr<Player> RankedMatch::getWinner() const {
    return m_players[m_winnerIndex];
}

// Displays a ranked match: match ID, average MMR, each player, and the winner
void RankedMatch::display(std::ostream& os) const {
    os << "--- Ranked Match #" << m_matchId
       << " (Avg MMR: " << m_averageMmr << ") ---\n";
    for (const auto& p : m_players) {
        os << "  " << *p << "\n";
    }
    os << "  Winner: " << m_players[m_winnerIndex]->getName() << "\n";
}
