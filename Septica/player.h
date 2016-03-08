#ifndef PLAYER_H
#define PLAYER_H

#include "genericplayer.h"
#include <string>

class Player final : public GenericPlayer
{
public:
    Player(const std::string& name = "");

    bool IsCutting(const Table& tbl = Table{}) const override;
    std::vector<Card*>::iterator SelectCard(const Table& tbl = Table{}) override;
};

#endif // PLAYER_H
