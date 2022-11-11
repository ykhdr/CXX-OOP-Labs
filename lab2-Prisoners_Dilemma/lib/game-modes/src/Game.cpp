#include "Game.h"

#include "StrategyFactory.h"

/*
    Всю логику игры реаоищовать здесь и далее пользоваться ей уже в gamemode.
*/

Game::Game(std::vector<std::string> strategiesNames, int moves) : playingField_(PlayingField(moves + 1))
{
    StrategyFactory *factory = &StrategyFactory::getInstance();

    for (int i = 0; i < 3; i++)
    {
        std::shared_ptr<IStrategy> player = factory->create(strategiesNames[i]);

        players_.push_back(player);
    }
}

void Game::makeMove()
{
    if (currentMove_ == 1)
    {
        playingField_.makeMoves(players_, "1", currentMove_);
    }
    else
    {
        playingField_.makeMoves(players_, playingField_.getLine(currentMove_ - 1), currentMove_);
    }

    playingField_.countMoveResult(playingField_.getLine(currentMove_), currentMove_);
    ++currentMove_;
}

void Game::printGameStatus()
{
    playingField_.printGameStatus(currentMove_ - 1);
}

void Game::finishGame()
{
    playingField_.printGameResult();
}