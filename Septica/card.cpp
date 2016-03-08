#include "card.h"

Card::Card(Rank r, Suit s, bool ifp, bool ifc): rank{r}, suit{s},
                                             is_point{ifp}, is_cut{ifc}
{
    if(r == Card::TEN || r == Card::ACE)
        is_point = true;

    if(r == Card::SEVEN)
        is_cut = true;
}

int Card::GetValue(void) const
{return rank;}

bool Card::IsPoint(void) const
{return is_point;}

bool Card::IsCut(void) const
{return is_cut;}

std::ostream& operator<<(std::ostream& os, const Card& card)
{
    static const std::string RANKS[] = {"7", "8", "9", "10", "A", "J", "Q", "K"};
    static const std::string SUITS[] = {"c", "d", "h", "s"};

    return os << RANKS[card.rank] << SUITS[card.suit];
}
