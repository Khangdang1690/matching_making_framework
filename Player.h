#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

class Player {
protected:
    int         m_id;
    std::string m_name;
    int         m_mmr;

public:
    Player(int id, const std::string& name, int mmr);
    virtual ~Player();

    int                getId()   const;
    const std::string& getName() const;
    int                getMmr()  const;

    void setMmr(int mmr);

    virtual void display(std::ostream& os = std::cout) const;

    friend std::ostream& operator<<(std::ostream& os, const Player& player);
};

#endif // PLAYER_H
