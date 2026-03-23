#include "Matchmaker.h"
#include <algorithm>
#include <iostream>

Matchmaker::Matchmaker(int teamSize, int maxMmrGap)
    : m_teamSize(teamSize), m_maxMmrGap(maxMmrGap), m_nextMatchId(1) {}

void Matchmaker::enqueue(std::shared_ptr<Player> player) {
    std::cout << "  Enqueued: " << player->getName()
              << " (MMR: " << player->getMmr() << ")\n";
    m_waitingQueue.push(std::move(player));
}

int Matchmaker::formMatches() {
    if (static_cast<int>(m_waitingQueue.size()) < m_teamSize)
        return 0;

    // Drain queue into a vector for sorting
    std::vector<std::shared_ptr<Player>> pool;
    pool.reserve(m_waitingQueue.size());
    while (!m_waitingQueue.empty()) {
        pool.push_back(m_waitingQueue.front());
        m_waitingQueue.pop();
    }

    // Build matches from the pool
    std::vector<Match> newMatches = buildMatchesFromPool(pool);

    // Unmatched players go back into the queue
    for (auto& p : pool) {
        m_waitingQueue.push(std::move(p));
    }

    int count = static_cast<int>(newMatches.size());
    for (auto& m : newMatches) {
        m_completedMatches.push_back(std::move(m));
    }

    return count;
}

std::vector<Match> Matchmaker::buildMatchesFromPool(
    std::vector<std::shared_ptr<Player>>& pool)
{
    // Sort by MMR ascending
    std::sort(pool.begin(), pool.end(),
        [](const std::shared_ptr<Player>& a, const std::shared_ptr<Player>& b) {
            return a->getMmr() < b->getMmr();
        });

    std::vector<Match> matches;
    std::vector<std::shared_ptr<Player>> unmatched;

    int i = 0;
    int n = static_cast<int>(pool.size());

    while (i + m_teamSize <= n) {
        int lo = pool[i]->getMmr();
        int hi = pool[i + m_teamSize - 1]->getMmr();

        if (hi - lo <= m_maxMmrGap) {
            // Valid match
            Match match;
            match.matchId = m_nextMatchId++;
            match.players.assign(pool.begin() + i, pool.begin() + i + m_teamSize);

            int sum = 0;
            for (auto& p : match.players) sum += p->getMmr();
            match.averageMmr = sum / m_teamSize;

            matches.push_back(std::move(match));
            i += m_teamSize;
        } else {
            // Lowest player in window can't match — skip to unmatched
            unmatched.push_back(pool[i]);
            i += 1;
        }
    }

    // Remaining players who didn't fill a complete group
    while (i < n) {
        unmatched.push_back(pool[i]);
        i++;
    }

    // Replace pool with unmatched (caller puts them back in queue)
    pool = std::move(unmatched);

    return matches;
}

int Matchmaker::getQueueSize() const {
    return static_cast<int>(m_waitingQueue.size());
}

const std::vector<Match>& Matchmaker::getCompletedMatches() const {
    return m_completedMatches;
}

void Matchmaker::displayQueue() const {
    if (m_waitingQueue.empty()) {
        std::cout << "  Queue is empty.\n";
        return;
    }

    // Copy queue to iterate without modifying original
    std::queue<std::shared_ptr<Player>> temp = m_waitingQueue;
    while (!temp.empty()) {
        std::cout << "  " << *temp.front() << "\n";
        temp.pop();
    }
}

void Matchmaker::displayMatches() const {
    if (m_completedMatches.empty()) {
        std::cout << "  No matches formed yet.\n";
        return;
    }

    for (const auto& match : m_completedMatches) {
        std::cout << "--- Match #" << match.matchId
                  << " (Avg MMR: " << match.averageMmr << ") ---\n";
        for (const auto& p : match.players) {
            std::cout << "  " << *p << "\n";
        }
    }
}
