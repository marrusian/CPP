#include "hand.h"

Hand::Hand() {cards.reserve(4);}

Hand::~Hand()
{ Clear(); }

void Hand::Add(Card* card)
{cards.push_back(card);}

void Hand::Place(std::vector<Card*>::iterator pos, Card* card)
{
    if(pos != cards.end())
        cards.insert(pos+1, card);

    // throw ...
}

void Hand::Remove(std::vector<Card*>::iterator card)
{cards.erase(card);}

bool Hand::IsEmpty(void) const
{return cards.empty();}

void Hand::Clear(void)
{
    for(auto iter = cards.begin(), it_end = cards.end(); iter != it_end; ++iter)
    {
        delete *iter;
        *iter = nullptr;
    }

    cards.clear();
}
