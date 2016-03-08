#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <vector>

class Hand
{
public:
    Hand();

    virtual ~Hand();

    // Adds a card to hand
    void Add(Card* card);

    // Place a card in hand
    void Place(std::vector<Card*>::iterator pos, Card* card);

    // Clear hand of all cards
    virtual void Clear(void);

    // Removes a card from hand
    void Remove(std::vector<Card*>::iterator card);

    // Check if hand is empty
    bool IsEmpty(void) const;

protected:
    std::vector<Card*> cards;
};

#endif // HAND_H
