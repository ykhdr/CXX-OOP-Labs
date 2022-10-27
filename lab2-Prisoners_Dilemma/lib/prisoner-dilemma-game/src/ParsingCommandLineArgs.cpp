#include "ParsingCommandLineArgs.h"

ParsingCommandLineArgs::ParsingCommandLineArgs()
{}

void ParsingCommandLineArgs::initialize(Game &game)
{
    stringValuesMap_["--mode"] = evMode;
    stringValuesMap_["--steps"] = evSteps;

    game.commandList_.emplace("start", &Game::setUpGame);
    game.commandList_.emplace("quit", &Game::endGame);
    game.commandList_.emplace("", &Game::continueGame);

    Factory *factory = &Factory::getInstance();

    factory->registerCreator("simple", std::make_shared<Creator<SimpleStrategy>>());
    factory->registerCreator("default", std::make_shared<Creator<DefaultStrategy>>());
    factory->registerCreator("random", std::make_shared<Creator<RandomStrategy>>());

}

bool ParsingCommandLineArgs::parseLine(Game &game)
{

    initialize(game);

    for (int i = 1; i < game.argc_; ++i)
    {
        if (std::find(game.strategiesList_.begin(), game.strategiesList_.end(), game.argv_[i]) !=
            game.strategiesList_.end())
        {
            game.players_.emplace_back(game.argv_[i]);
            continue;
        }

        if (game.argv_[i][0] == '-' && game.argv_[i][1] == '-')
        {
            auto fPos = game.argv_[i].find('=');

            if (fPos == -1 || fPos == game.argv_.size() - 1)
            {
                std::cout << "\t\t\tParameter entered incorrectly";
            }

            std::string_view argView = game.argv_[i];

            switch (stringValuesMap_[argView.substr(0, fPos)])
            {
                case evMode:
                    std::cout << "evMode" << std::endl;

                    break;

                case evSteps:
                    std::cout << "evSteps" << std::endl;

                    try
                    {
                        game.numOfMoves_ = std::stoi(game.argv_[i].substr(fPos + 1));

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
                    break;

            }
        }

    }

    if (game.players_.size() < 3)
    {
        while (game.players_.size() != 3)
        {
            game.players_.emplace_back("default");
        }
    }
    else
    {
        game.numOfPrisoners = game.players_.size();
    }

    return false;
}




