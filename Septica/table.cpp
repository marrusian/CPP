#include "table.h"
#include "genericplayer.h"

Table::Table(GenericPlayer* gplayer):
                    starting_player{gplayer}, hand_winner{starting_player},
                    hand_points{0}
{ }

void Table::Clear(void)
{
    Hand::Clear();
    hand_points = 0;
    starting_player = hand_winner;
}

int Table::GetTablePoints(void) const
{return hand_points;}

const Card* Table::GetStartingCard(void) const
{return cards.front();}

bool Table::IsHandCut(const Card* card) const
{
    return ((cards.front()->GetValue() == card->GetValue()) || card->IsCut());
}

std::vector<Card*>::iterator Table::RequestCard(GenericPlayer& current_player)
{
    std::vector<Card*>::iterator temp_card = current_player.SelectCard(*this);
    Add(*temp_card);
    current_player.Remove(temp_card);

    return temp_card;
}

void Table::ReturnLastCard(GenericPlayer& current_player, std::vector<Card*>::iterator pos)
{
    current_player.Place(pos, cards.back());
    Remove(cards.end() - 1);
}

void Table::UpdateWinner(GenericPlayer& current_player)
{
    if(cards.size() > 1)
    {
        // Check if last card placed on table cuts the previous one
        if(IsHandCut(cards.back()))
        {
            hand_winner = &current_player;
        }
    }
}

void Table::UpdatePoints(void)
{
    if(cards.back()->IsPoint())
        ++hand_points;
}

std::ostream& operator<<(std::ostream& os, const Table& table)
{
    for(Card* x : table.cards)
        os << *x << ' ';

    return os;
}


