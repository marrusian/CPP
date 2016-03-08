#include "game.h"
#include <iostream>
#include <vector>
#include <string>
#include <cctype>

int main()
{
    std::cout << "\t\t\tSeptica\n\n";

    int num_players = 0, num_ai = -1;
    constexpr int MAX_PLAYERS = 4;

    while(num_players < 1 || num_players > MAX_PLAYERS)
    {
        std::cout << "How many players? (1 - " << MAX_PLAYERS << "): ";
        std::cin >> num_players;
    }

    if(num_players != MAX_PLAYERS)
    {
        while(num_ai < 0 || num_ai > (MAX_PLAYERS-num_players))
        {
            std::cout << "How many AIs? (0 - " << (MAX_PLAYERS-num_players) << "): ";
            std::cin >> num_ai;
        }
    }

    std::vector<std::string> pnames, ainames;
    std::string name;
    for(int i=0; i < num_players; ++i)
    {
        std::cout << "Enter player name: ";
        std::cin >> name;
        pnames.push_back(name);
    }

    for(int i=0; i < num_ai; ++i)
    {
        std::cout << "Enter AI name: ";
        std::cin >> name;
        ainames.push_back(name);
    }
    std::cout << std::endl;

    char play_again = 'Y';
    while((toupper(play_again) != 'N') && std::cin)
    {
          Game game(pnames, ainames);
          game.Play();
          std::cout << "\nDo you want to play again? (Y/N): ";
          std::cin >> play_again;

          // Discard extra characters
           std::cin.clear();
           for(char temp = '\0'; temp != '\n'; std::cin.get(temp))
               continue;
    }

    return 0;
}

