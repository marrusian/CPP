#ifndef TABLE_H
#define TABLE_H

#include "hand.h"

class GenericPlayer;

class Table final : public Hand
{
    friend class Game;
    friend std::ostream& operator<<(std::ostream& os, const Table& table);

public:
    Table(GenericPlayer* gplayer = nullptr);

    std::vector<Card*>::iterator RequestCard(GenericPlayer& current_player);
    void ReturnLastCard(GenericPlayer& current_player, std::vector<Card*>::iterator);

    void UpdateWinner(GenericPlayer& current_player);
    void UpdatePoints(void);

    void Clear(void) override;

    int GetTablePoints(void) const;
    const Card* GetStartingCard(void) const;

    bool IsHandCut(const Card* card) const;

private:
    GenericPlayer* starting_player;
    GenericPlayer* hand_winner;
    int hand_points;
};

#endif // TABLE_H
