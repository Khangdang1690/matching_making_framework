#ifndef RANKED_PLAYER_H
#define RANKED_PLAYER_H

#include "Player.h"
#include <string>

// Derived class representing a competitive ranked player.
// Inherits from Player and adds a rank tier, win/loss tracking,
// and an overridden display method to show ranked-specific info.
class RankedPlayer : public Player {
public:
    // Rank tiers from lowest to highest skill level
    enum class Tier {
        Bronze,
        Silver,
        Gold,
        Platinum,
        Diamond
    };

private:
    Tier m_tier;    // Player's current rank tier
    int  m_wins;    // Total number of wins
    int  m_losses;  // Total number of losses

public:
    // Constructor: creates a ranked player with tier and optional win/loss record
    RankedPlayer(int id, const std::string& name, int mmr,
                 Tier tier, int wins = 0, int losses = 0);

    // Destructor override for proper cleanup through base class pointer
    ~RankedPlayer() override;

    // Getters
    Tier   getTier()    const;
    int    getWins()    const;
    int    getLosses()  const;

    // Calculates win rate as a percentage (0.0 - 100.0)
    double getWinRate() const;

    // Increments the win counter by one
    void recordWin();

    // Increments the loss counter by one
    void recordLoss();

    // Updates the player's rank tier
    void setTier(Tier tier);

    // Overrides Player::display to include tier and win/loss stats
    void display(std::ostream& os = std::cout) const override;

    // Converts a Tier enum value to a readable string (e.g., Tier::Gold -> "Gold")
    static std::string tierToString(Tier tier);
};

#endif // RANKED_PLAYER_H
