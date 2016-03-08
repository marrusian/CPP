#ifndef AI_H
#define AI_H

#include "genericplayer.h"
#include <string>

class AI final : public GenericPlayer
{
public:
    AI(const std::string& nm = "", int pts = 0);

    bool IsCutting(const Table& tbl) const override;
    std::vector<Card*>::iterator SelectCard(const Table& tbl) override;
};

#endif // AI_H
