#include "Game.h"

namespace
{
    void welcomeMessage()
    {
        std::cout << "\n\t\t\tGame \"Prisoner's Dilemma\"\n\n " <<
                  "\tTo start the game write \'start\'\n" <<
                  "\tTo end the game write \'quit\'\n" << std::endl;
    }

}

void Game::parseParams()
{
    for (int i = 1; i < argc_; ++i)
    {
        if (std::find(listOfStrategies_.begin(), listOfStrategies_.end(), argv_[i]) != listOfStrategies_.end())
        {
            players_.emplace_back(argv_[i]);
        }
        else
        {
            //TODO: сделать парс параметров здесь
        }
    }

}

bool Game::setUpGame()
{
    if (isGameStarted_)
    {
        std::cout << "Game is already started" << std::endl;
        return false;
    }



    std::vector<std::string_view> v = {"1"};
    for (int i = 0; i < players_.size(); ++i)
    {
        playingField_.moveMatrix_.addMove(i, players_[i].makeMove(v));
    }


    std::cout << "setUpGame" << std::endl;
    for (int i = 0; i < numOfPrisoners; ++i)
    {
        std::cout << playingField_.getLine(1)[i] << " ";
    }

    isGameStarted_ = true;
    return false;
}

bool Game::endGame()
{
    std::cout << "endGame" << std::endl;

    return true;
}

bool Game::continueGame()
{
    std::cout << "contgame" << std::endl;
    return false;
}

Game::Game(int argc, const char **argv) : argc_(argc)
{
    for (int i = 0; i < argc; ++i)
    {
        this->argv_.emplace_back(argv[i]);
    }

}

void Game::setUpCommands()
{
    commands_.insert(std::make_pair("start", &Game::setUpGame));
    commands_.emplace("quit", &Game::endGame);
    commands_.emplace("", &Game::continueGame);
}

void Game::run()
{

    parseParams();
    setUpCommands();

    welcomeMessage();

    std::string inputMessage;

    while (true)
    {
        std::getline(std::cin, inputMessage);

        MFP fp = commands_[inputMessage];

        if (fp == nullptr)
        {
            std::cout << "\tYou entered the wrong message. Try again." << std::endl;
            continue;
        }
        if ((this->*fp)())
        {
            return;
        }

    }

}

Game::~Game()
{

}








