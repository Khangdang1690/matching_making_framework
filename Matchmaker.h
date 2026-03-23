#ifndef MATCHMAKER_H
#define MATCHMAKER_H

#include "Player.h"
#include "Queue.h"
#include <vector>
#include <memory>

// Represents a completed match — a group of players paired together
struct Match {
    int                                  matchId;      // Unique match identifier
    std::vector<std::shared_ptr<Player>> players;      // Players in this match
    int                                  averageMmr;   // Average MMR of the group
};

// Matchmaker manages the player waiting queue and forms balanced matches.
// Uses a custom Queue backed by a templated circularly linked list.
class Matchmaker {
private:
    Queue<std::shared_ptr<Player>> m_waitingQueue;     // Players waiting to be matched
    std::vector<Match>             m_completedMatches;  // History of all formed matches
    int                            m_teamSize;          // Players needed per match
    int                            m_maxMmrGap;         // Max MMR difference allowed in a match
    int                            m_nextMatchId;       // Auto-incrementing match ID

public:
    // Constructor: sets team size and maximum MMR gap for matching
    Matchmaker(int teamSize = 2, int maxMmrGap = 200);

    // Adds a player to the waiting queue
    void enqueue(std::shared_ptr<Player> player);

    // Attempts to form matches from queued players; returns number of matches formed
    int  formMatches();

    // Returns the number of players currently waiting in the queue
    int getQueueSize() const;

    // Returns the list of all completed matches
    const std::vector<Match>& getCompletedMatches() const;

    // Prints all players currently in the waiting queue
    void displayQueue()   const;

    // Prints all completed matches with player details
    void displayMatches() const;

private:
    // Sorts players by MMR and groups them into valid matches using a sliding window
    std::vector<Match> buildMatchesFromPool(
        std::vector<std::shared_ptr<Player>>& pool);
};

#endif // MATCHMAKER_H
