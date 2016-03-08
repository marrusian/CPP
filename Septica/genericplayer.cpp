#include "genericplayer.h"
#include "player.h"
#include <typeinfo>

GenericPlayer::GenericPlayer(const std::string& pname, int pts)
                        : name{pname}, points{pts}
{ }

int& GenericPlayer::Points(void)
{return points;}

bool GenericPlayer::HasCard(const Card* card) const
{
    for(Card* x : cards)
        if(x->GetValue() == card->GetValue())
            return true;

    return false;
}

bool GenericPlayer::HasCut(void) const
{
    for(Card* x : cards)
        if(x->IsCut())
            return true;

    return false;
}

void GenericPlayer::Win(void) const
{std::cout << name << " wins with " << points << " points!" << std::endl;}

std::ostream& operator<<(std::ostream& os, const GenericPlayer& gp)
{
    os << gp.name << ":\t";

    if(!gp.cards.empty())
    {
        if(typeid(gp) == typeid(Player))
        {
            for(Card* card : gp.cards)
                os << *card << '\t';
        }
        else
        {
            for(Card* card : gp.cards)
                os << "XX" << '\t';
        }

        os << std::endl << gp.name << "'s points: " << gp.points;
    }

    return os;
}
