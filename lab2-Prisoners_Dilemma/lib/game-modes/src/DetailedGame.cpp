#include "DetailedGame.h"

DetailedGame::DetailedGame(std::vector<std::string> strategiesNames, int &moves) : game_(Game(std::move(strategiesNames), moves)), moves_(moves) {}

void DetailedGame::initialize()
{
    userInputValuesMap_["start"] = UserInputValues::evStart;
    userInputValuesMap_[""] = UserInputValues::evContinue;
    userInputValuesMap_["quit"] = UserInputValues::evQuit;
}

void DetailedGame::run()
{
    initialize();

    std::string inputMessage;

    for (int i = 0; i < moves_;)
    {
        std::getline(std::cin, inputMessage);

        switch (userInputValuesMap_[inputMessage])
        {
        case UserInputValues::evStart:
            std::cout << "\t\t\tGame already started" << std::endl;
            continue;

        case UserInputValues::evContinue:
            game_.makeMove();
            game_.printGameStatus();
            break;

        case UserInputValues::evQuit:
            return;

        default:
            std::cout << "\t\t\tYou entered the wrong message. Try again." << std::endl;
            continue;
        }

        ++i;
    }

    game_.finishGame();
}