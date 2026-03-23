// Main driver for the Matchmaking Queue System.
// Two match types: Normal (casual) and Ranked (competitive).
// Each has its own queue and matchmaker. All players are the same.

#include "Player.h"
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
static Player::Tier readTier() {
    std::cout << "  Pick a rank: 1=Bronze  2=Silver  3=Gold  4=Platinum  5=Diamond\n";
    while (true) {
        int choice = readInt("  Rank (1-5): ");
        switch (choice) {
            case 1: return Player::Tier::Bronze;
            case 2: return Player::Tier::Silver;
            case 3: return Player::Tier::Gold;
            case 4: return Player::Tier::Platinum;
            case 5: return Player::Tier::Diamond;
            default: std::cout << "  Pick 1-5.\n";
        }
    }
}

int main() {
    std::cout << "========================================\n"
              << "       MATCHMAKING QUEUE SYSTEM\n"
              << "========================================\n\n"

              << "This program simulates online game matchmaking\n"
              << "with two match types:\n\n"

              << "  NORMAL MATCH  - casual, just for fun\n"
              << "  RANKED MATCH  - competitive, picks a winner\n\n"

              << "Every player has a name, MMR, and rank.\n"
              << "  MMR  = skill rating (higher = better)\n"
              << "  Rank = Bronze, Silver, Gold, Platinum, or Diamond\n\n"

              << "How it works:\n"
              << "  1. Add players to the Normal or Ranked queue.\n"
              << "  2. \"Find Matches\" groups similar-skill players.\n"
              << "  3. Players too far apart in skill stay in the queue.\n"
              << "  4. Ranked matches also determine a winner!\n\n"

              << "Setup:\n"
              << "  Team Size   = players per match (enter 2 for 1v1)\n"
              << "  Max MMR Gap = biggest skill gap allowed (enter 200)\n\n"

              << "========================================\n\n";

    // Prompt user for matchmaker configuration
    int teamSize  = readInt("Team size (players per match): ");
    int maxMmrGap = readInt("Max MMR gap: ");

    // Two matchmakers: normal (casual) and ranked (competitive)
    Matchmaker normalMM(teamSize, maxMmrGap, false);
    Matchmaker rankedMM(teamSize, maxMmrGap, true);
    int nextId = 1;  // Shared auto-incrementing player ID

    // Main menu loop
    while (true) {
        std::cout << "\n=== Menu ===\n"
                  << "1. Join Normal Match\n"
                  << "2. Join Ranked Match\n"
                  << "3. View Queues\n"
                  << "4. Find Matches\n"
                  << "5. View Match History\n"
                  << "6. Exit\n";
        int choice = readInt("> ");

        switch (choice) {
        case 1: {
            // Add a player to the normal (casual) queue
            std::string name = readString("  Name: ");
            int mmr = readInt("  MMR: ");
            Player::Tier tier = readTier();
            normalMM.enqueue(std::make_shared<Player>(nextId++, name, mmr, tier));
            break;
        }
        case 2: {
            // Add a player to the ranked (competitive) queue
            std::string name = readString("  Name: ");
            int mmr = readInt("  MMR: ");
            Player::Tier tier = readTier();
            rankedMM.enqueue(std::make_shared<Player>(nextId++, name, mmr, tier));
            break;
        }
        case 3:
            // Show both queues
            std::cout << "\n--- Normal Queue (" << normalMM.getQueueSize() << " players) ---\n";
            normalMM.displayQueue();
            std::cout << "\n--- Ranked Queue (" << rankedMM.getQueueSize() << " players) ---\n";
            rankedMM.displayQueue();
            break;
        case 4: {
            // Run matchmaking on both queues separately
            std::cout << "\n--- Normal Matches ---\n";
            int nFormed = normalMM.formMatches();
            std::cout << "Formed " << nFormed << " normal match(es).";
            if (normalMM.getQueueSize() > 0)
                std::cout << " " << normalMM.getQueueSize() << " still waiting.";
            std::cout << "\n";

            std::cout << "\n--- Ranked Matches ---\n";
            int rFormed = rankedMM.formMatches();
            std::cout << "Formed " << rFormed << " ranked match(es).";
            if (rankedMM.getQueueSize() > 0)
                std::cout << " " << rankedMM.getQueueSize() << " still waiting.";
            std::cout << "\n";
            break;
        }
        case 5:
            // Show match history for both types
            std::cout << "\n--- Normal Match History ---\n";
            normalMM.displayMatches();
            std::cout << "\n--- Ranked Match History ---\n";
            rankedMM.displayMatches();
            break;
        case 6:
            std::cout << "Goodbye!\n";
            return 0;
        default:
            std::cout << "Invalid choice. Pick 1-6.\n";
        }
    }
}
