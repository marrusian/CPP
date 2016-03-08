#include "player.h"
#include <iostream>
#include <cctype>

Player::Player(const std::string& name): GenericPlayer{name}
{ }

bool Player::IsCutting(const Table& /* dummy */) const
{
    char answer;

    std::cout << name << ", do you want to cut? (Y/N): ";
    std::cin >> answer;

   // Discard extra characters
    std::cin.clear();
    for(char temp = '\0'; temp != '\n'; std::cin.get(temp))
        continue;

    return (toupper(answer) == 'Y');
}

std::vector<Card*>::iterator Player::SelectCard(const Table& /* dummy */)
{
    auto card_position = cards.size();

    while((card_position < 1 || card_position >= cards.size()) && std::cin){
        std::cout << name << ", select a card from your hand (1 to "
                  << cards.size() << "): ";
        std::cin >> card_position;

        if(card_position-1 < cards.size())
            return cards.begin()+(card_position-1);
    }

    return cards.end();
}

