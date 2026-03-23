#ifndef RANKED_PLAYER_H
#define RANKED_PLAYER_H

#include "Player.h"
#include <string>

class RankedPlayer : public Player {
public:
    enum class Tier {
        Bronze,
        Silver,
        Gold,
        Platinum,
        Diamond
    };

private:
    Tier m_tier;
    int  m_wins;
    int  m_losses;

public:
    RankedPlayer(int id, const std::string& name, int mmr,
                 Tier tier, int wins = 0, int losses = 0);
    ~RankedPlayer() override;

    Tier   getTier()    const;
    int    getWins()    const;
    int    getLosses()  const;
    double getWinRate() const;

    void recordWin();
    void recordLoss();
    void setTier(Tier tier);

    void display(std::ostream& os = std::cout) const override;

    static std::string tierToString(Tier tier);
};

#endif // RANKED_PLAYER_H
