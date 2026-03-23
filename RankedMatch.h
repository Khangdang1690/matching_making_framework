#ifndef RANKED_MATCH_H
#define RANKED_MATCH_H

#include "Match.h"

// Derived class representing a competitive ranked match.
// Inherits from Match and adds a simulated match result:
// picks the highest-MMR player as the winner.
class RankedMatch : public Match {
private:
    int m_winnerIndex;  // Index of the winning player in m_players

public:
    // Constructor: creates a ranked match and determines a winner
    RankedMatch(int id, std::vector<std::shared_ptr<Player>> players, int avgMmr);

    // Destructor override
    ~RankedMatch() override;

    // Returns a pointer to the winning player
    std::shared_ptr<Player> getWinner() const;

    // Overrides display to show "Ranked Match" label and the winner
    void display(std::ostream& os = std::cout) const override;
};

#endif // RANKED_MATCH_H
