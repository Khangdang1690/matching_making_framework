#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

// Base class representing a casual player in the matchmaking system.
// Stores player ID, name, and MMR (Matchmaking Rating) which indicates skill level.
// RankedPlayer inherits from this class to add competitive features.
class Player {
protected:
    int         m_id;    // Unique player identifier
    std::string m_name;  // Player's display name
    int         m_mmr;   // Matchmaking Rating — higher means more skilled

public:
    // Constructor: creates a player with the given ID, name, and MMR
    Player(int id, const std::string& name, int mmr);

    // Virtual destructor for safe polymorphic deletion
    virtual ~Player();

    // Getters
    int                getId()   const;
    const std::string& getName() const;
    int                getMmr()  const;

    // Sets a new MMR value for this player
    void setMmr(int mmr);

    // Prints player info to the given stream; overridden by RankedPlayer
    virtual void display(std::ostream& os = std::cout) const;

    // Stream insertion operator — delegates to virtual display() for polymorphism
    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

#endif // PLAYER_H
