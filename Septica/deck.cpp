#include "deck.h"
#include <algorithm>

Deck::Deck()
{
    cards.reserve(32);
    FillDeck();
}

void Deck::FillDeck(int num_players)
{
    Clear();

    // Create Deck
    for(int st = Card::CLUBS; st <= Card::SPADES; ++st)
    {
        for(int rnk = Card::SEVEN; rnk <= Card::KING; ++rnk)
        {
            Add(new Card(static_cast<Card::Rank>(rnk), static_cast<Card::Suit>(st)));
        }
    }

    // When there are 3 players: - Discard two eights
    //                           - Make the remaining eights points
    if(num_players == 3)
    {
        for(int i=0; i<2; ++i)
            cards[i*(Card::KING+1)+Card::EIGHT]->is_point = true;
        for(int i=2; i<4; ++i)
        {
            delete cards[i*(Card::KING+1) + Card::EIGHT - (i-2)];
            cards.erase(cards.begin() + i*(Card::KING+1) + Card::EIGHT - (i-2));
        }
    }
}

void Deck::Shuffle(void)
{std::random_shuffle(cards.begin(), cards.end());}

void Deck::Deal(Hand& hand)
{
    if(cards.empty())
        std::cout << "Deck is empty. Unable to deal!";

    hand.Add(cards.back());
    cards.pop_back();
}
