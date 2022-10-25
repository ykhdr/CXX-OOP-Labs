#include "Game.h"
#include <getopt.h>

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
    parsing = new ParsingCommandLineArgs;

    for (int i = 0; i < argc; ++i)
    {
        this->argv_.emplace_back(argv[i]);
    }

    if (argc - 1 > numOfPrisoners)
    {
        numOfPrisoners = argc - 1;
    }

    playingField_ = PlayingField(numOfMoves_, numOfPrisoners);
}

bool Game::setUpGame()
{
    if (isGameStarted_)
    {
        std::cout << "Game is already started" << std::endl;
        return false;
    }

    playingField_.makeMoves(players_, "1",currentMove_);
    playingField_.countResult(playingField_.getLine(currentMove_),currentMove_);

    std::cout << "\t\t\tThe game starts!\n\t\t\tFirst moves:\n" << std::endl;

    playingField_.printGameStatus(currentMove_);

    isGameStarted_ = true;

    ++currentMove_;

    return false;
}

bool Game::endGame()
{
    std::cout << "endGame" << std::endl;

    return true;
}

bool Game::continueGame()
{
    //system("clear");

    if (!isGameStarted_)
    {
        std::cout << "\t\t\tGame hasn't started yet" << std::endl;
        return false;
    }

    playingField_.makeMoves(players_, playingField_.getLine(currentMove_),currentMove_);
    playingField_.countResult(playingField_.getLine(currentMove_),currentMove_);

    playingField_.printGameStatus(currentMove_);

    if (currentMove_ == numOfMoves_ - 1)
    {
        std::cout << "\n\t\t\t Game over!\n" << std::endl;
        return true;
    }

    ++currentMove_;

    return false;
}

void Game::setUpCommands()
{
    commandList_.insert(std::make_pair("start", &Game::setUpGame));
    commandList_.emplace("quit", &Game::endGame);
    commandList_.emplace("", &Game::continueGame);

    Factory *factory = &Factory::getInstance();

    factory->registerCreator("simple",std::make_shared<Creator<SimpleStrategy>>());
    factory->registerCreator("default",std::make_shared<Creator<DefaultStrategy>>());
    factory->registerCreator("random",std::make_shared<Creator<RandomStrategy>>());
}

void Game::run()
{
    setUpCommands();

    parsing->parseLine(*this);
    //parseParams();


    //system("clear");

    welcomeMessage();

    std::string inputMessage;

    while (true)
    {
        std::getline(std::cin, inputMessage);

        MFP fp = commandList_[inputMessage];

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
    delete parsing;
}









