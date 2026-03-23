#include "RankedPlayer.h"
#include <iomanip>

// Constructor: initializes base Player and ranked-specific fields
RankedPlayer::RankedPlayer(int id, const std::string& name, int mmr,
                           Tier tier, int wins, int losses)
    : Player(id, name, mmr), m_tier(tier), m_wins(wins), m_losses(losses) {}

// Destructor override (empty body — no additional resources to free)
RankedPlayer::~RankedPlayer() {}

// Returns the player's current rank tier
RankedPlayer::Tier RankedPlayer::getTier()    const { return m_tier; }

// Returns the total number of wins
int                RankedPlayer::getWins()    const { return m_wins; }

// Returns the total number of losses
int                RankedPlayer::getLosses()  const { return m_losses; }

// Calculates win rate as a percentage; returns 0.0 if no games played
double RankedPlayer::getWinRate() const {
    int total = m_wins + m_losses;
    if (total == 0) return 0.0;
    return static_cast<double>(m_wins) / total * 100.0;
}

// Records a win for this player
void RankedPlayer::recordWin()  { ++m_wins; }

// Records a loss for this player
void RankedPlayer::recordLoss() { ++m_losses; }

// Updates the player's rank tier
void RankedPlayer::setTier(Tier tier) { m_tier = tier; }

// Displays ranked player info including tier and win/loss record
void RankedPlayer::display(std::ostream& os) const {
    os << "[RankedPlayer #" << m_id << "] " << m_name
       << " (MMR: " << m_mmr << ") | Tier: " << tierToString(m_tier)
       << " | W/L: " << m_wins << "/" << m_losses
       << " (" << std::fixed << std::setprecision(1) << getWinRate() << "%)";
}

// Converts a Tier enum to its string representation
std::string RankedPlayer::tierToString(Tier tier) {
    switch (tier) {
        case Tier::Bronze:   return "Bronze";
        case Tier::Silver:   return "Silver";
        case Tier::Gold:     return "Gold";
        case Tier::Platinum: return "Platinum";
        case Tier::Diamond:  return "Diamond";
        default:             return "Unknown";
    }
}
