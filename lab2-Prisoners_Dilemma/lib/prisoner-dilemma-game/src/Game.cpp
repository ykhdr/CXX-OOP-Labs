#include "Game.h"

/**
 * D - предать, C - молчать
 *
 *
 */


namespace
{
    void welcomeMessage()
    {
        std::cout << "\n\t\t\tGame \"Prisoner's Dilemma\"\n\n " <<
                  "\tTo start the game write \'start\'\n" <<
                  "\tTo end the game write \'quit\'\n" << std::endl;
    }
}

Game::Game(int argc, const char **argv) : argc_(argc)
{

    for (int i = 0; i < argc; ++i)
    {
        this->argv_.emplace_back(argv[i]);
    }

    if (argc - 1 > numOfPrisoners)
    {
        numOfPrisoners = argc - 1;
    }


}

bool Game::setUpGame()
{
    if (isGameStarted_)
    {
        std::cout << "Game is already started" << std::endl;
        return false;
    }

    playingField_.makeMoves(players_, "1", currentMove_);
    playingField_.countResult(playingField_.getLine(currentMove_), currentMove_);

    std::cout << "\t\t\tThe game starts!\n\t\t\tFirst moves:\n" << std::endl;

    playingField_.printGameStatus(currentMove_);

    if (currentMove_ == numOfMoves_)
    {
        std::cout << "\n\t\t\t Game over!\n" << std::endl;
        return true;
    }

    ++currentMove_;

    isGameStarted_ = true;

    srand(time(NULL));

    return false;
}

bool Game::continueGame()
{
    if (!isGameStarted_)
    {
        std::cout << "\t\t\tGame hasn't started yet" << std::endl;
        return false;
    }

    playingField_.makeMoves(players_, playingField_.getLine(currentMove_ - 1), currentMove_);
    playingField_.countResult(playingField_.getLine(currentMove_), currentMove_);
    playingField_.printGameStatus(currentMove_);

    if (currentMove_ == numOfMoves_)
    {
        std::cout << "\n\t\t\t Game over!\n" << std::endl;
        playingField_.printGameResult();
        return true;
    }

    ++currentMove_;

    return false;
}

bool Game::endGame()
{

    return true;
}

void Game::run()
{
    if (parsing->parseLine(*this))
    {
        return;
    }

    playingField_ = PlayingField(numOfMoves_ + 1, numOfPrisoners);

    welcomeMessage();

    std::string inputMessage;

    while (true)
    {
        std::getline(std::cin, inputMessage);

        pGameFun fp = commandMap_[inputMessage];

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

Game::~Game()
{
}









