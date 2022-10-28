#include "ParsingCommandLineArgs.h"

void ParsingCommandLineArgs::initialize(Game &game)
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

bool ParsingCommandLineArgs::parseCommand(Game &game, std::string &str)
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

bool ParsingCommandLineArgs::parseLine(Game &game)
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
        game.numOfPrisoners = game.players_.size();
    }

    return false;
}







