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


bool setUpGame()
{
    std::cout << "setUpGame" << std::endl;
    return false;
}

bool endGame()
{
    std::cout << "endGame" <<  std::endl;

    return true;
}

bool continueGame()
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
    commands_.emplace("start", &setUpGame);
    commands_.emplace("quit", &endGame);
    commands_.emplace("", &continueGame);
    moveMatrix_.makeMatrix();
}

void Game::run()
{
    setUpCommands();
    welcomeMessage();

    std::string inputMessage;

    while (true)
    {
        std::getline(std::cin, inputMessage);
        try
        {
           auto gameFunction = commands_.at(inputMessage);

            if (gameFunction())
            {
                return;
            }

        } catch (std::out_of_range ex)
        {
            std::cout << "\tYou entered the wrong message. Try again." << std::endl;
            continue;
        }

    }

}

Game::~Game()
{

}






