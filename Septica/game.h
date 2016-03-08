#ifndef GAME_H
#define GAME_H

#include "deck.h"
#include "player.h"
#include "ai.h"
#include "table.h"
#include <string>
#include <vector>

class Game
{
public:
    Game(const std::vector<std::string>& pnames,
         const std::vector<std::string>& ainames);
    ~Game();

    // Simulate the game
    void Play(void);

private:
    Deck deck;
    std::vector<GenericPlayer*> players;
    Table table;
};

#endif // GAME_H
