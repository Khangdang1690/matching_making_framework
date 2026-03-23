#ifndef MATCHMAKER_H
#define MATCHMAKER_H

#include "Player.h"
#include "Match.h"
#include "RankedMatch.h"
#include "Queue.h"
#include <vector>
#include <memory>

// Matchmaker manages the player waiting queue and forms balanced matches.
// Uses a custom Queue backed by a templated circularly linked list.
// Can operate in normal or ranked mode.
class Matchmaker {
private:
    Queue<std::shared_ptr<Player>>       m_waitingQueue;     // Players waiting to be matched
    std::vector<std::shared_ptr<Match>>  m_completedMatches; // History of all formed matches
    int                                  m_teamSize;         // Players needed per match
    int                                  m_maxMmrGap;        // Max MMR difference allowed
    int                                  m_nextMatchId;      // Auto-incrementing match ID
    bool                                 m_ranked;           // True = ranked mode

public:
    // Constructor: sets team size, MMR gap, and whether this is ranked mode
    Matchmaker(int teamSize = 2, int maxMmrGap = 200, bool ranked = false);

    // Adds a player to the waiting queue
    void enqueue(std::shared_ptr<Player> player);

    // Attempts to form matches from queued players; returns number of matches formed
    int formMatches();

    // Returns the number of players currently waiting in the queue
    int getQueueSize() const;

    // Prints all players currently in the waiting queue
    void displayQueue() const;

    // Prints all completed matches with player details
    void displayMatches() const;

private:
    // Sorts players by MMR and groups them into valid matches using a sliding window
    std::vector<std::shared_ptr<Match>> buildMatchesFromPool(
        std::vector<std::shared_ptr<Player>>& pool);
};

#endif // MATCHMAKER_H
