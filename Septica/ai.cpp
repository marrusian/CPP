#include "ai.h"

AI::AI(const std::string& nm, int pts): GenericPlayer(nm, pts)
{ }

bool AI::IsCutting(const Table& tbl) const
{
    if(tbl.GetTablePoints() >= 1)
        return true;

    return false;
}

std::vector<Card*>::iterator AI::SelectCard(const Table& tbl)
{
    auto bloatCard_pos = cards.end();
    auto rankCard_pos = cards.end();
    auto pointCard_pos = cards.end();
    auto cutCard_pos = cards.end();

    for(auto it_card = cards.begin(), itEnd = cards.end();
        it_card != itEnd; ++it_card)
    {
        if(!tbl.IsEmpty() && tbl.GetStartingCard()->GetValue() == (*it_card)->GetValue())
            rankCard_pos = it_card;
        else if((*it_card)->IsCut())
            cutCard_pos = it_card;
        else if((*it_card)->IsPoint())
            pointCard_pos = it_card;
        else
            bloatCard_pos = it_card;
    }

    if(tbl.GetTablePoints() >= 1)
    {
        if(rankCard_pos != cards.end())
            return rankCard_pos;
        else if(cutCard_pos != cards.end())
            return cutCard_pos;
        else if(bloatCard_pos != cards.end())
            return bloatCard_pos;
        else
            return pointCard_pos;
    }
    else
    {
        if(rankCard_pos != cards.end())
            return rankCard_pos;
        else if(bloatCard_pos != cards.end())
            return bloatCard_pos;
        else if(pointCard_pos != cards.end())
            return pointCard_pos;
        else
            return cutCard_pos;
    }
}

