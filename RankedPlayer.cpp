#include "RankedPlayer.h"
#include <iomanip>

RankedPlayer::RankedPlayer(int id, const std::string& name, int mmr,
                           Tier tier, int wins, int losses)
    : Player(id, name, mmr), m_tier(tier), m_wins(wins), m_losses(losses) {}

RankedPlayer::~RankedPlayer() {}

RankedPlayer::Tier RankedPlayer::getTier()    const { return m_tier; }
int                RankedPlayer::getWins()    const { return m_wins; }
int                RankedPlayer::getLosses()  const { return m_losses; }

double RankedPlayer::getWinRate() const {
    int total = m_wins + m_losses;
    if (total == 0) return 0.0;
    return static_cast<double>(m_wins) / total * 100.0;
}

void RankedPlayer::recordWin()  { ++m_wins; }
void RankedPlayer::recordLoss() { ++m_losses; }
void RankedPlayer::setTier(Tier tier) { m_tier = tier; }

void RankedPlayer::display(std::ostream& os) const {
    os << "[RankedPlayer #" << m_id << "] " << m_name
       << " (MMR: " << m_mmr << ") | Tier: " << tierToString(m_tier)
       << " | W/L: " << m_wins << "/" << m_losses
       << " (" << std::fixed << std::setprecision(1) << getWinRate() << "%)";
}

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
