#include "Player.h"
#include "RankedPlayer.h"
#include "Matchmaker.h"
#include <iostream>
#include <memory>
#include <vector>

int main() {
    // --- Create players (mix of Player and RankedPlayer) ---
    std::vector<std::shared_ptr<Player>> players = {
        std::make_shared<Player>(1,  "Alice",   1200),
        std::make_shared<Player>(2,  "Bob",     1150),
        std::make_shared<RankedPlayer>(3,  "Charlie", 1180, RankedPlayer::Tier::Gold,     50, 30),
        std::make_shared<RankedPlayer>(4,  "Diana",   1500, RankedPlayer::Tier::Platinum,  80, 20),
        std::make_shared<Player>(5,  "Eve",     1520),
        std::make_shared<RankedPlayer>(6,  "Frank",   900,  RankedPlayer::Tier::Bronze,   10, 40),
        std::make_shared<Player>(7,  "Grace",   920),
        std::make_shared<Player>(8,  "Hank",    1800),
        std::make_shared<RankedPlayer>(9,  "Ivy",     1750, RankedPlayer::Tier::Diamond, 100, 15),
        std::make_shared<Player>(10, "Jack",    1400),
        std::make_shared<RankedPlayer>(11, "Karen",   1420, RankedPlayer::Tier::Gold,     60, 25),
        std::make_shared<Player>(12, "Leo",     600),
    };

    // --- Display all players ---
    std::cout << "=== All Players ===\n";
    for (const auto& p : players) {
        std::cout << "  " << *p << "\n";
    }

    // --- Enqueue all players ---
    std::cout << "\n=== Enqueuing Players ===\n";
    Matchmaker matchmaker(2, 200);  // teamSize=2, maxMmrGap=200

    for (auto& p : players) {
        matchmaker.enqueue(p);
    }
    std::cout << "Queue size: " << matchmaker.getQueueSize() << "\n";

    // --- Run matchmaking ---
    std::cout << "\n=== Running Matchmaker (Team Size: 2, Max MMR Gap: 200) ===\n";
    int formed = matchmaker.formMatches();
    std::cout << "Formed " << formed << " match(es).\n\n";
    matchmaker.displayMatches();

    // --- Show remaining queue ---
    std::cout << "\n=== Players Still Waiting ===\n";
    matchmaker.displayQueue();

    // --- Add late arrivals near outlier MMRs ---
    std::cout << "\n=== Adding Late Arrivals ===\n";
    matchmaker.enqueue(std::make_shared<Player>(13, "Mike",  620));
    matchmaker.enqueue(std::make_shared<Player>(14, "Nancy", 1780));

    // --- Re-run matchmaking ---
    std::cout << "\n=== Re-running Matchmaker ===\n";
    formed = matchmaker.formMatches();
    std::cout << "Formed " << formed << " match(es).\n\n";

    // --- Display all completed matches ---
    std::cout << "=== All Completed Matches ===\n";
    matchmaker.displayMatches();

    // --- Final queue status ---
    std::cout << "\n=== Final Queue Status ===\n";
    matchmaker.displayQueue();

    return 0;
}
