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

void Game::ParsingCommandLineArgs::initialize(Game &game)
{
    stringValuesMap_["--mode"] = evMode;
    stringValuesMap_["--steps"] = evSteps;

    game.commandMap_.emplace("start", &Game::setUpGame);
    game.commandMap_.emplace("quit", &Game::endGame);
    game.commandMap_.emplace("", &Game::continueGame);

    Factory *factory = &Factory::getInstance();

    factory->registerCreator("simple", std::make_shared<Creator<SimpleStrategy>>());
    factory->registerCreator("default", std::make_shared<Creator<DefaultStrategy>>());
    factory->registerCreator("random", std::make_shared<Creator<RandomStrategy>>());
    factory->registerCreator("smart", std::make_shared<Creator<SmartStrategy>>());
}

bool Game::ParsingCommandLineArgs::parseCommand(Game &game, std::string &str)
{
    auto fPos = str.find('=');

    if (fPos == -1 || fPos == str.size() - 1)
    {
        std::cout << "\t\t\tParameter entered incorrectly";
        return true;
    }

    std::string_view argView = str;

    switch (stringValuesMap_[argView.substr(0, fPos)])
    {
        case evMode:
            std::cout << "evMode" << std::endl;

            break;

        case evSteps:
            try
            {
                game.numOfMoves_ = std::stoi(str.substr(fPos + 1));

                if (game.numOfMoves_ <= 0)
                {
                    throw std::exception();
                }

            } catch (std::exception &ex)
            {
                std::cout << "\t\t\t" << "You entered wrong --steps param" << std::endl;
                return true;
            }

            break;

        default:
            std::cout << "\t\t\tParameter entered incorrectly" << std::endl;
            return true;

    }
    return false;
}

bool Game::ParsingCommandLineArgs::parseLine(Game &game)
{
    initialize(game);

    Factory *factory = &Factory::getInstance();

    for (int i = 1; i < game.argc_; ++i)
    {
        std::shared_ptr<IStrategy> player = factory->create(game.argv_[i]);

        if (player != nullptr)
        {
            game.players_.push_back(player);
            continue;
        }

        if (game.argv_[i][0] == '-' && game.argv_[i][1] == '-')
        {
            if (parseCommand(game, game.argv_[i]))
            {
                return true;
            }
            continue;
        }

        std::cout << "\t\t\tParameter entered incorrectly" << std::endl;
        return true;
    }

    if (game.players_.size() < 3)
    {
        while (game.players_.size() != 3)
        {
            game.players_.push_back(factory->create("default"));
        }
    } else
    {
        game.numOfPrisoners_ = game.players_.size();
    }

    return false;
}


Game::Game(int argc, const char **argv) : argc_(argc)
{

    for (int i = 0; i < argc; ++i)
    {
        this->argv_.emplace_back(argv[i]);
    }

    if (argc - 1 > numOfPrisoners_)
    {
        numOfPrisoners_ = argc - 1;
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
    if (parsing_->parseLine(*this))
    {
        return;
    }

    playingField_ = PlayingField(numOfMoves_ + 1, numOfPrisoners_);

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









