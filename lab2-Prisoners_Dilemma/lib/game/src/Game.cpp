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

void Game::ParsingCommandLineArgs::initialize(Game &game)
{
    stringValuesMap_["--steps"] = evSteps;
    stringValuesMap_["--mode"] = evMode;

    StrategyFactory *factory = &StrategyFactory::getInstance();

    factory->registerCreator("simple", std::make_shared<Creator<SimpleStrategy>>());
    factory->registerCreator("default", std::make_shared<Creator<DefaultStrategy>>());
    factory->registerCreator("random", std::make_shared<Creator<RandomStrategy>>());
    factory->registerCreator("smart", std::make_shared<Creator<SmartStrategy>>());
    factory->registerCreator("person", std::make_shared<Creator<PersonStrategy>>());
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

            if (!game.gameModeName_.empty())
            {
                std::cout << "\t\t\tYou have already chosen game mode" << std::endl;
                return true;
            }

            game.gameModeName_ = argView.substr(fPos + 1);

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

    std::vector<std::shared_ptr<IStrategy>> players;

    StrategyFactory *factory = &StrategyFactory::getInstance();

    for (int i = 1; i < game.argc_; ++i)
    {
        std::shared_ptr<IStrategy> player = factory->create(game.argv_[i]);

        if (player != nullptr)
        {
            players.push_back(player);
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

    if (players.size() < 3)
    {
        while (players.size() != 3)
        {
            players.push_back(factory->create("default"));
        }
    }

    if (game.gameModeName_.empty())
    {
        if(players.size()>3)
        {
            game.gameMode_ = std::make_unique<TournamentGameMode>(std::move(players), game.numOfMoves_);
        } else
        {
            game.gameMode_ = std::make_unique<DetailedGameMode>(std::move(players), game.numOfMoves_);
        }
        return false;
    }
    if (game.gameModeName_ == "detailed")
    {
        game.gameMode_ = std::make_unique<DetailedGameMode>(std::move(players), game.numOfMoves_);
        return false;
    }
    if (game.gameModeName_ == "fast")
    {
        game.gameMode_ = std::make_unique<FastGameMode>(std::move(players), game.numOfMoves_);
        return false;
    }
    if (game.gameModeName_ == "tournament")
    {
        game.gameMode_ = std::make_unique<TournamentGameMode>(std::move(players), game.numOfMoves_);
        return false;
    }

    std::cout << "Name of game mode entered incorrectly" << std::endl;
    return true;

}

Game::Game(int argc, const char **argv) : argc_(argc)
{
    for (int i = 0; i < argc; ++i)
    {
        this->argv_.emplace_back(argv[i]);
    }
}

void Game::run()
{
    srand(time(NULL));

    if (parsing_->parseLine(*this))
    {
        return;
    }

    welcomeMessage();

    gameMode_->run();

}

Game::~Game()
{
}