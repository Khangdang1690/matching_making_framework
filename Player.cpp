#include "Player.h"

Player::Player(int id, const std::string& name, int mmr)
    : m_id(id), m_name(name), m_mmr(mmr) {}

Player::~Player() {}

int Player::getId() const { return m_id; }
const std::string& Player::getName() const { return m_name; }
int Player::getMmr() const { return m_mmr; }

void Player::setMmr(int mmr) { m_mmr = mmr; }

void Player::display(std::ostream& os) const {
    os << "[Player #" << m_id << "] " << m_name << " (MMR: " << m_mmr << ")";
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    player.display(os);
    return os;
}
