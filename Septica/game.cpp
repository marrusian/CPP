#include "game.h"
#include <ctime>
#include <algorithm>

Game::Game(const std::vector<std::string>& pnames,
           const std::vector<std::string>& ainames)
{
    // Add players and AIs to the game
    for(auto &nm : pnames)
    { players.push_back(new Player(nm)); }

    for(auto &nm : ainames)
    { players.push_back(new AI(nm)); }

    // if(!players.size() || players.size() > 4)
    //   throw ...

    // Create the deck
    std::srand(static_cast<unsigned int>(time(nullptr)));
    deck.FillDeck(players.size());
    deck.Shuffle();

    // Let the first player start the game
    table.starting_player = table.hand_winner = players.front();
}

Game::~Game()
{
    for(auto& x : players)
        delete x;
}

void Game::Play(void)
{
    bool is_continuing;
    bool is_cutting;
    int cards_dealt = 0;
    std::vector<Card*>::iterator card_pos;

    // Deal initial 4 cards to each player
    for(int i=0; i<4; ++i)
    {
        for(auto& player : players)
        {
            deck.Deal(*player);
        }
    }

    while(!players.front()->IsEmpty())
    {
        cards_dealt = 0;
        is_continuing = true;
        is_cutting = false;

        while(is_continuing)
        {
            // Display each players' hand
            for(auto& player: players)
            {
                std::cout << *player << std::endl;
            }

            ++cards_dealt;
            for(auto& player : players)
            {
                card_pos = table.RequestCard(*player);
                if(is_cutting)
                    while(!table.IsHandCut(table.cards.back()))
                    {
                        std::cout << "Illegal card. Place a cutting card!\n";
                        table.ReturnLastCard(*player, card_pos);
                        table.RequestCard(*player);
                    }
                is_cutting = false;

                table.UpdateWinner(*player);
                table.UpdatePoints();
                std::cout << table << std::endl;
            }
            std::cout << std::endl;

            if(table.hand_winner == table.starting_player)
            {
                table.starting_player->Points() += table.hand_points;
                is_continuing = false;
            }
            else if((table.starting_player->HasCut()
                    || table.starting_player->HasCard(table.cards.front()))
                    && table.starting_player->IsCutting(table))
            {
                    is_cutting = true;
                    continue;
            }
            else
            {
                table.hand_winner->Points() += table.hand_points;
                is_continuing = false;
            }
        }

        // Remove cards from table and reset table points
        table.Clear();

        // Refill players' hands
        for(int i=0; i<cards_dealt && !deck.IsEmpty(); ++i)
            for(auto& player : players)
            {
                deck.Deal(*player);
            }

        std::swap(players.front(), *std::find(players.begin(), players.end(), table.hand_winner));
    }


    // Find Winner
    auto& winner = players.front();
    for(auto& player : players)
        if(player->Points() > winner->Points())
            winner = player;

    // Announce Winner (or Tie)
    if(players.size() > 1)
    {
        if(winner == players.front() && winner->Points() == players[1]->Points())
            std::cout << "It's a tie!" << std::endl;
        else
            winner->Win();
    }
}

