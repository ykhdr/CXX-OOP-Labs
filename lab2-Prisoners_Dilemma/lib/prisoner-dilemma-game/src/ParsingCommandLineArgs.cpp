#include "ParsingCommandLineArgs.h"

ParsingCommandLineArgs::ParsingCommandLineArgs()
{
    //stringValuesMap_[""];
}

void ParsingCommandLineArgs::initialize(Game &game)
{
    stringValuesMap_["--mode"] = evMode;
    stringValuesMap_["--steps"] = evSteps;

    game.commandList_.insert(std::make_pair("start", &Game::setUpGame));
    game.commandList_.emplace("quit", &Game::endGame);
    game.commandList_.emplace("", &Game::continueGame);

    Factory *factory = &Factory::getInstance();

    factory->registerCreator("simple",std::make_shared<Creator<SimpleStrategy>>());
    factory->registerCreator("default",std::make_shared<Creator<DefaultStrategy>>());
    factory->registerCreator("random",std::make_shared<Creator<RandomStrategy>>());

}

void ParsingCommandLineArgs::parseLine(Game &game)
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
            int fPos = game.argv_[i].find('=');
            std::string_view strView = game.argv_[i];
            switch (stringValuesMap_[strView.substr(0,-fPos)])
            {
                case evMode:

                    break;
                case evSteps:

                    break;
                default:

                    break;

            }
        }

    }

    if (game.players_.size() < 3)
    {
        while (game.players_.size() != 3)
        {
            game.players_.emplace_back("random");
        }
    }
}




