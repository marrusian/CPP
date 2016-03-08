#ifndef CARD_H
#define CARD_H

#include <iostream>

class Deck;

class Card
{
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    friend class Deck;

public:
    enum Rank{SEVEN, EIGHT, NINE, TEN, ACE, JACK, QUEEN, KING};
    enum Suit{CLUBS, DIAMONDS, HEARTS, SPADES};

    Card(Rank r = SEVEN, Suit s = CLUBS, bool ifp = false, bool isc = false);

    int GetValue(void) const;
    bool IsPoint(void) const;
    bool IsCut(void) const;

private:
    Rank rank;
    Suit suit;
    bool is_point;
    bool is_cut;
};

#endif // CARD_H
