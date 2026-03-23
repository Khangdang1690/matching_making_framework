#include "Matchmaker.h"
#include <algorithm>
#include <iostream>

// Constructor: initializes matchmaker with team size and MMR gap settings
Matchmaker::Matchmaker(int teamSize, int maxMmrGap)
    : m_teamSize(teamSize), m_maxMmrGap(maxMmrGap), m_nextMatchId(1) {}

// Adds a player to the waiting queue and prints confirmation
void Matchmaker::enqueue(std::shared_ptr<Player> player) {
    std::cout << "  Enqueued: " << player->getName()
              << " (MMR: " << player->getMmr() << ")\n";
    m_waitingQueue.enqueue(std::move(player));
}

// Drains the queue, forms matches from the pool, and returns unmatched players
// to the queue. Returns the number of matches formed this cycle.
int Matchmaker::formMatches() {
    if (m_waitingQueue.size() < m_teamSize)
        return 0;

    // Drain the circular linked list queue into a vector for sorting
    std::vector<std::shared_ptr<Player>> pool;
    while (!m_waitingQueue.isEmpty()) {
        pool.push_back(m_waitingQueue.dequeue());
    }

    // Build matches from the sorted pool
    std::vector<Match> newMatches = buildMatchesFromPool(pool);

    // Unmatched players go back into the queue
    for (auto& p : pool) {
        m_waitingQueue.enqueue(std::move(p));
    }

    // Store the newly formed matches in history
    int count = static_cast<int>(newMatches.size());
    for (auto& m : newMatches) {
        m_completedMatches.push_back(std::move(m));
    }

    return count;
}

// Sorts players by MMR ascending, then uses a greedy sliding window
// to group consecutive players whose MMR spread is within the max gap.
// Players that can't be matched are left in the pool vector.
std::vector<Match> Matchmaker::buildMatchesFromPool(
    std::vector<std::shared_ptr<Player>>& pool)
{
    // Sort by MMR so similar-skill players are adjacent
    std::sort(pool.begin(), pool.end(),
        [](const std::shared_ptr<Player>& a, const std::shared_ptr<Player>& b) {
            return a->getMmr() < b->getMmr();
        });

    std::vector<Match> matches;
    std::vector<std::shared_ptr<Player>> unmatched;

    int i = 0;
    int n = static_cast<int>(pool.size());

    // Sliding window: try to group teamSize consecutive players
    while (i + m_teamSize <= n) {
        int lo = pool[i]->getMmr();
        int hi = pool[i + m_teamSize - 1]->getMmr();

        if (hi - lo <= m_maxMmrGap) {
            // MMR gap is acceptable — form a valid match
            Match match;
            match.matchId = m_nextMatchId++;
            match.players.assign(pool.begin() + i, pool.begin() + i + m_teamSize);

            // Calculate the average MMR for this match
            int sum = 0;
            for (auto& p : match.players) sum += p->getMmr();
            match.averageMmr = sum / m_teamSize;

            matches.push_back(std::move(match));
            i += m_teamSize;
        } else {
            // MMR gap too large — skip the lowest player to unmatched
            unmatched.push_back(pool[i]);
            i += 1;
        }
    }

    // Any remaining players who didn't fill a complete group
    while (i < n) {
        unmatched.push_back(pool[i]);
        i++;
    }

    // Replace pool with unmatched players (caller puts them back in queue)
    pool = std::move(unmatched);

    return matches;
}

// Returns the number of players currently waiting in the queue
int Matchmaker::getQueueSize() const {
    return m_waitingQueue.size();
}

// Returns a const reference to the completed matches history
const std::vector<Match>& Matchmaker::getCompletedMatches() const {
    return m_completedMatches;
}

// Prints all players currently in the waiting queue
void Matchmaker::displayQueue() const {
    if (m_waitingQueue.isEmpty()) {
        std::cout << "  Queue is empty.\n";
        return;
    }

    // Use the Queue's display method to traverse the circular linked list
    m_waitingQueue.display(std::cout);
}

// Prints all completed matches with match ID, average MMR, and player details
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
