#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

// Base class representing a player in the matchmaking system.
// Every player has an ID, name, MMR (skill rating), and a rank tier.
class Player {
public:
    // Rank tiers from lowest to highest
    enum class Tier {
        Bronze,
        Silver,
        Gold,
        Platinum,
        Diamond
    };

protected:
    int         m_id;    // Unique player identifier
    std::string m_name;  // Player's display name
    int         m_mmr;   // Matchmaking Rating — higher means more skilled
    Tier        m_tier;  // Player's rank tier

public:
    // Constructor: creates a player with the given ID, name, MMR, and tier
    Player(int id, const std::string& name, int mmr, Tier tier);

    // Virtual destructor for safe polymorphic deletion
    virtual ~Player();

    // Getters
    int                getId()   const;
    const std::string& getName() const;
    int                getMmr()  const;
    Tier               getTier() const;

    // Sets a new MMR value for this player
    void setMmr(int mmr);

    // Prints player info to the given stream; overridden by RankedPlayer
    virtual void display(std::ostream& os = std::cout) const;

    // Converts a Tier enum value to a readable string (e.g., Tier::Gold -> "Gold")
    static std::string tierToString(Tier tier);

    // Stream insertion operator — delegates to virtual display() for polymorphism
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

#endif // PLAYER_H
