#ifndef MATCHMAKER_H
#define MATCHMAKER_H

#include "Player.h"
#include <vector>
#include <queue>
#include <memory>

struct Match {
    int                                  matchId;
    std::vector<std::shared_ptr<Player>> players;
    int                                  averageMmr;
};

class Matchmaker {
private:
    std::queue<std::shared_ptr<Player>> m_waitingQueue;
    std::vector<Match>                  m_completedMatches;
    int                                 m_teamSize;
    int                                 m_maxMmrGap;
    int                                 m_nextMatchId;

public:
    Matchmaker(int teamSize = 2, int maxMmrGap = 200);

    void enqueue(std::shared_ptr<Player> player);
    int  formMatches();

    int getQueueSize() const;
    const std::vector<Match>& getCompletedMatches() const;

    void displayQueue()   const;
    void displayMatches() const;

private:
    std::vector<Match> buildMatchesFromPool(
        std::vector<std::shared_ptr<Player>>& pool);
};

#endif // MATCHMAKER_H
