#include "Player.h"

// Constructor: initializes player with ID, name, MMR, and rank tier
Player::Player(int id, const std::string& name, int mmr, Tier tier)
    : m_id(id), m_name(name), m_mmr(mmr), m_tier(tier) {}

// Virtual destructor (default body for base class cleanup)
Player::~Player() {}

// Returns the player's unique ID
int Player::getId() const { return m_id; }

// Returns a const reference to the player's name
const std::string& Player::getName() const { return m_name; }

// Returns the player's MMR (skill rating)
int Player::getMmr() const { return m_mmr; }

// Returns the player's rank tier
Player::Tier Player::getTier() const { return m_tier; }

// Updates the player's MMR to a new value
void Player::setMmr(int mmr) { m_mmr = mmr; }

// Displays player info: [Player #id] name | Rank | MMR
void Player::display(std::ostream& os) const {
    os << "[Player #" << m_id << "] " << m_name
       << " | " << tierToString(m_tier)
       << " | MMR: " << m_mmr;
}

// Converts a Tier enum to its string representation
std::string Player::tierToString(Tier tier) {
    switch (tier) {
        case Tier::Bronze:   return "Bronze";
        case Tier::Silver:   return "Silver";
        case Tier::Gold:     return "Gold";
        case Tier::Platinum: return "Platinum";
        case Tier::Diamond:  return "Diamond";
        default:             return "Unknown";
    }
}

// Stream operator delegates to display() so polymorphism works correctly
std::ostream& operator<<(std::ostream& os, const Player& player) {
    player.display(os);
    return os;
}
