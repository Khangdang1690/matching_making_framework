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

// Prompts the user to pick a rank tier (Bronze through Diamond)
static RankedPlayer::Tier readTier() {
    std::cout << "  Pick a rank: 1=Bronze  2=Silver  3=Gold  4=Platinum  5=Diamond\n";
    while (true) {
        int choice = readInt("  Rank (1-5): ");
        switch (choice) {
            case 1: return RankedPlayer::Tier::Bronze;
            case 2: return RankedPlayer::Tier::Silver;
            case 3: return RankedPlayer::Tier::Gold;
            case 4: return RankedPlayer::Tier::Platinum;
            case 5: return RankedPlayer::Tier::Diamond;
            default: std::cout << "  Pick 1-5.\n";
        }
    }
}

int main() {
    std::cout << "========================================\n"
              << "       MATCHMAKING QUEUE SYSTEM\n"
              << "========================================\n\n"

              << "This program simulates online game matchmaking.\n"
              << "It groups players with similar skill into fair matches.\n\n"

              << "QUICK START:\n"
              << "  1. First, enter a Team Size and Max MMR Gap (see below).\n"
              << "  2. Add a few players (option 1) or ranked players (option 2).\n"
              << "     - Give each player a name and an MMR (skill rating).\n"
              << "     - MMR is just a number: higher = more skilled.\n"
              << "       Example: 800 = beginner, 1200 = average, 1800 = expert\n"
              << "     - Ranked players also have a rank (Bronze-Diamond)\n"
              << "       and a win/loss record, showing inheritance in action.\n"
              << "  3. Select \"Find Matches\" (option 4) to pair them up.\n"
              << "     - Players within the MMR gap get matched together.\n"
              << "     - Players too far apart in skill stay in the queue.\n"
              << "  4. View results with \"View Match History\" (option 5).\n\n"

              << "SETUP (enter these now):\n"
              << "  Team Size   = players needed per match\n"
              << "                (enter 2 for 1v1, or 4 for 2v2)\n"
              << "  Max MMR Gap = largest skill gap allowed in one match\n"
              << "                (enter 200 for a good demo)\n\n"

              << "========================================\n\n";

    // Prompt user for matchmaker configuration
    int teamSize  = readInt("Team size (players per match): ");
    int maxMmrGap = readInt("Max MMR gap: ");

    // Create the matchmaker with user-specified settings
    Matchmaker matchmaker(teamSize, maxMmrGap);
    int nextId = 1;  // Auto-incrementing player ID

    // Main menu loop — runs until user selects Exit
    while (true) {
        std::cout << "\n=== Menu ===\n"
                  << "1. Add Player\n"
                  << "2. Add Ranked Player\n"
                  << "3. View Queue\n"
                  << "4. Find Matches\n"
                  << "5. View Match History\n"
                  << "6. Exit\n";
        int choice = readInt("> ");

        switch (choice) {
        case 1: {
            // Add a casual player (name + MMR only)
            std::string name = readString("  Name: ");
            int mmr = readInt("  MMR (skill rating): ");
            matchmaker.enqueue(std::make_shared<Player>(nextId++, name, mmr));
            break;
        }
        case 2: {
            // Add a ranked player (name + MMR + rank + win/loss record)
            std::string name = readString("  Name: ");
            int mmr = readInt("  MMR (skill rating): ");
            RankedPlayer::Tier tier = readTier();
            int wins   = readInt("  Wins: ");
            int losses = readInt("  Losses: ");
            matchmaker.enqueue(std::make_shared<RankedPlayer>(
                nextId++, name, mmr, tier, wins, losses));
            break;
        }
        case 3:
            // Show all players currently waiting in the queue
            std::cout << "\n=== Queue (" << matchmaker.getQueueSize() << " players) ===\n";
            matchmaker.displayQueue();
            break;
        case 4: {
            // Run the matchmaker to pair up players with similar MMR
            std::cout << "\n=== Finding Matches ===\n";
            int formed = matchmaker.formMatches();
            std::cout << "Formed " << formed << " match(es).\n";
            if (matchmaker.getQueueSize() > 0) {
                std::cout << matchmaker.getQueueSize() << " player(s) still waiting.\n";
            }
            break;
        }
        case 5:
            // Display all previously formed matches
            std::cout << "\n=== Match History ===\n";
            matchmaker.displayMatches();
            break;
        case 6:
            std::cout << "Goodbye!\n";
            return 0;
        default:
            std::cout << "Invalid choice. Pick 1-6.\n";
        }
    }
}
