// Main driver for the Matchmaking Queue System.
// Provides an interactive menu for adding players, viewing the queue,
// running the matchmaker, and viewing match history.

#include "Player.h"
#include "RankedPlayer.h"
#include "Matchmaker.h"
#include <iostream>
#include <memory>
#include <string>
#include <limits>

// Prompts the user for an integer, retrying on invalid input
static int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Invalid input. Please enter a number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Prompts the user for a string using getline (supports spaces in names)
static std::string readString(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

// Displays the tier options and prompts the user to select one (1-5)
static RankedPlayer::Tier readTier() {
    std::cout << "  Select tier:\n"
              << "    1. Bronze\n"
              << "    2. Silver\n"
              << "    3. Gold\n"
              << "    4. Platinum\n"
              << "    5. Diamond\n";
    while (true) {
        int choice = readInt("  Tier (1-5): ");
        switch (choice) {
            case 1: return RankedPlayer::Tier::Bronze;
            case 2: return RankedPlayer::Tier::Silver;
            case 3: return RankedPlayer::Tier::Gold;
            case 4: return RankedPlayer::Tier::Platinum;
            case 5: return RankedPlayer::Tier::Diamond;
            default: std::cout << "Invalid choice. Pick 1-5.\n";
        }
    }
}

int main() {
    std::cout << "============================================================\n"
              << "       MULTIPLAYER GAME MATCHMAKING QUEUE SYSTEM\n"
              << "============================================================\n\n"

              << "Welcome! This program simulates how online multiplayer games\n"
              << "match players into fair, balanced games.\n\n"

              << "--- KEY CONCEPTS ---\n\n"

              << "MMR (Matchmaking Rating):\n"
              << "  A number representing a player's skill level.\n"
              << "  Higher MMR = stronger player. Example ranges:\n"
              << "    0-800    Beginner\n"
              << "    800-1200 Intermediate\n"
              << "    1200-1600 Advanced\n"
              << "    1600-2000 Expert\n\n"

              << "Player vs Ranked Player:\n"
              << "  - Player: A casual player with just a name and MMR.\n"
              << "  - Ranked Player: A competitive player who also has a rank\n"
              << "    tier (Bronze -> Silver -> Gold -> Platinum -> Diamond)\n"
              << "    and a win/loss record.\n\n"

              << "How Matchmaking Works:\n"
              << "  1. Players join a waiting queue.\n"
              << "  2. The matchmaker groups players with similar MMR together.\n"
              << "  3. If players are too far apart in skill (beyond the Max\n"
              << "     MMR Gap), they won't be placed in the same match.\n"
              << "  4. Unmatched players stay in the queue for next time.\n\n"

              << "--- SETUP ---\n\n"

              << "Team Size: How many players are needed to start a match.\n"
              << "  (e.g., 2 for a 1v1, 10 for a 5v5)\n\n"

              << "Max MMR Gap: The largest skill difference allowed between\n"
              << "  players in the same match. Smaller = fairer but slower.\n"
              << "  (e.g., 200 is a good starting value)\n\n"

              << "============================================================\n\n";

    // Prompt user for matchmaker configuration
    int teamSize  = readInt("Team size (players per match): ");
    int maxMmrGap = readInt("Max MMR gap: ");

    // Create the matchmaker with user-specified settings
    Matchmaker matchmaker(teamSize, maxMmrGap);
    int nextId = 1;  // Auto-incrementing player ID

    // Main menu loop — runs until user selects Exit
    while (true) {
        std::cout << "\n=== Matchmaking System ===\n"
                  << "1. Add Player\n"
                  << "2. Add Ranked Player\n"
                  << "3. View Queue\n"
                  << "4. Run Matchmaker\n"
                  << "5. View Match History\n"
                  << "6. Exit\n";
        int choice = readInt("> ");

        switch (choice) {
        case 1: {
            std::string name = readString("  Name: ");
            int mmr = readInt("  MMR: ");
            matchmaker.enqueue(std::make_shared<Player>(nextId++, name, mmr));
            break;
        }
        case 2: {
            std::string name = readString("  Name: ");
            int mmr = readInt("  MMR: ");
            RankedPlayer::Tier tier = readTier();
            int wins   = readInt("  Wins: ");
            int losses = readInt("  Losses: ");
            matchmaker.enqueue(std::make_shared<RankedPlayer>(
                nextId++, name, mmr, tier, wins, losses));
            break;
        }
        case 3:
            std::cout << "\n=== Queue (" << matchmaker.getQueueSize() << " players) ===\n";
            matchmaker.displayQueue();
            break;
        case 4: {
            std::cout << "\n=== Running Matchmaker (Team Size: " << teamSize
                      << ", Max MMR Gap: " << maxMmrGap << ") ===\n";
            int formed = matchmaker.formMatches();
            std::cout << "Formed " << formed << " match(es).\n";
            if (matchmaker.getQueueSize() > 0) {
                std::cout << matchmaker.getQueueSize() << " player(s) still waiting.\n";
            }
            break;
        }
        case 5:
            std::cout << "\n=== Match History ===\n";
            matchmaker.displayMatches();
            break;
        case 6:
            std::cout << "Exiting.\n";
            return 0;
        default:
            std::cout << "Invalid choice. Pick 1-6.\n";
        }
    }
}
