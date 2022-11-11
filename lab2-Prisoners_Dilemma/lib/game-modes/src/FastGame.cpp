#include "FastGame.h"

FastGame::FastGame(std::vector<std::string> strategiesNames, int &moves) : game_(Game(std::move(strategiesNames), moves)), moves_(moves) {}

void FastGame::run()
{
    for (int i = 0; i < moves_; i++)
    {
        game_.makeMove();
    }
    
    game_.printGameStatus();
    game_.finishGame();
}