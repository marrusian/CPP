#ifndef DECK_H
#define DECK_H

#include "hand.h"

class GenericPlayer;

class Deck final : public Hand
{
public:
    Deck();

    void FillDeck(int num_players = 2);
    void Shuffle(void);
    void Deal(Hand& hand);
};

#endif // DECK_H
