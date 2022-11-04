#include "DetailedGameMode.h"

namespace
{
    void printCommandMessage()
    {
        std::cout << "\tTo start the game write \'start\'\n" <<
                  "\tTo end the game write \'quit\'\n" << std::endl;
    }
}

DetailedGameMode::DetailedGameMode(std::vector<std::shared_ptr<IStrategy>> &&players, int &moves) :
        players_(players), movesNum_(moves)
{
    playingField_ = PlayingField(movesNum_ + 1);

    commandMap_.emplace("start", &DetailedGameMode::setUpGame);
    commandMap_.emplace("quit", &DetailedGameMode::endGame);
    commandMap_.emplace("", &DetailedGameMode::continueGame);
}

void DetailedGameMode::run()
{
    printCommandMessage();

    std::string inputMessage;

    while (true)
    {
        std::getline(std::cin, inputMessage);

        pGameModeFun fp = commandMap_[inputMessage];

        if (fp == nullptr)
        {
            std::cout << "\t\tYou entered the wrong message. Try again." << std::endl;
            continue;
        }

        if ((this->*fp)())
        {
            return;
        }

        std::cout << "\n\t\t\tPress enter for next move\n" << std::endl;
    }
}

bool DetailedGameMode::setUpGame()
{

    if (isGameStarted_)
    {
        std::cout << "Game is already started" << std::endl;
        return false;
    }

    playingField_.makeMoves(players_, "1", currentMove_);
    playingField_.countMoveResult(playingField_.getLine(currentMove_), currentMove_);

    std::cout << "\t\t\tThe game starts!\n\t\t\tFirst moves:\n" << std::endl;

    playingField_.printGameStatus(currentMove_);

    if (currentMove_ == movesNum_)
    {
        std::cout << "\n\t\t\t Game over!\n" << std::endl;
        return true;
    }

    ++currentMove_;

    isGameStarted_ = true;

    srand(time(NULL));

    return false;
}


bool DetailedGameMode::continueGame()
{
    if (!isGameStarted_)
    {
        std::cout << "\t\t\tGame hasn't started yet" << std::endl;
        return false;
    }

    playingField_.makeMoves(players_, playingField_.getLine(currentMove_ - 1), currentMove_);
    playingField_.countMoveResult(playingField_.getLine(currentMove_), currentMove_);
    playingField_.printGameStatus(currentMove_);

    if (currentMove_ == movesNum_)
    {
        std::cout << "\n\t\t\t Game over!\n" << std::endl;
        playingField_.printGameResult();
        return true;
    }

    ++currentMove_;

    return false;
}

bool DetailedGameMode::endGame()
{
    return true;
}