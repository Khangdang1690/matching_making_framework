#include "Player.h"

// Constructor: initializes player with ID, name, and MMR via initializer list
Player::Player(int id, const std::string& name, int mmr)
    : m_id(id), m_name(name), m_mmr(mmr) {}

// Virtual destructor (default body for base class cleanup)
Player::~Player() {}

// Returns the player's unique ID
int Player::getId() const { return m_id; }

// Returns a const reference to the player's name
const std::string& Player::getName() const { return m_name; }

// Returns the player's MMR (skill rating)
int Player::getMmr() const { return m_mmr; }

// Updates the player's MMR to a new value
void Player::setMmr(int mmr) { m_mmr = mmr; }

// Displays basic player info: [Player #id] name (MMR: value)
void Player::display(std::ostream& os) const {
    os << "[Player #" << m_id << "] " << m_name << " (MMR: " << m_mmr << ")";
}

// Stream operator delegates to display() so polymorphism works correctly.
// When called on a RankedPlayer through a Player reference, the overridden
// display() in RankedPlayer will be invoked.
std::ostream& operator<<(std::ostream& os, const Player& player) {
    player.display(os);
    return os;
}
