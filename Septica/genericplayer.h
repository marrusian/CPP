#ifndef GENERICPLAYER_H
#define GENERICPLAYER_H

#include "hand.h"
#include "table.h"
#include <string>
#include <iostream>

class GenericPlayer : public Hand
{
    friend std::ostream& operator<<(std::ostream& os, const GenericPlayer& gp);

public:
    GenericPlayer(const std::string& pname = " ", int pts = 0);

    virtual ~GenericPlayer() = default;

    virtual bool IsCutting(const Table& tbl = Table{}) const = 0;
    virtual std::vector<Card*>::iterator SelectCard(const Table& tbl = Table{}) = 0;

    int& Points(void);
    bool HasCard(const Card* card) const;
    bool HasCut(void) const;

    void Win(void) const;

protected:
    std::string name;
    int points;
};

#endif // GENERICPLAYER_H
