#ifndef MATCH_H
#define MATCH_H

#include "Player.h"
#include <vector>
#include <memory>
#include <iostream>

// Base class representing a normal (casual) match.
// Stores the players grouped together and their average MMR.
class Match {
protected:
    int                                  m_matchId;     // Unique match identifier
    std::vector<std::shared_ptr<Player>> m_players;     // Players in this match
    int                                  m_averageMmr;  // Average MMR of the group

public:
    // Constructor: creates a match with the given ID, players, and average MMR
    Match(int id, std::vector<std::shared_ptr<Player>> players, int avgMmr);

    // Virtual destructor for safe polymorphic deletion
    virtual ~Match();

    // Getters
    int getMatchId()    const;
    int getAverageMmr() const;
    const std::vector<std::shared_ptr<Player>>& getPlayers() const;

    // Displays match info; overridden by RankedMatch
    virtual void display(std::ostream& os = std::cout) const;
};

#endif // MATCH_H
