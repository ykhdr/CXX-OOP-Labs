#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <stdexcept>
#include <unordered_map>
#include <functional>

#include "Player.h"
#include "PlayingField.h"
#include "FastGameMod.h"
#include "MoveMatrix.h"
#include "TournamentGameMod.h"
#include "DetailedGameMod.h"
#include "StrategyFactory.h"
#include "../strategies/include/SimpleStrategy.h"

typedef void (*voidFunctionType)();

class Game
{
private:
    typedef bool (Game::*MFP)();

    bool isGameStarted_ = false;

    int argc_;
    std::vector<std::string> argv_;

    int numOfPrisoners = 3;
    int numOfMoves = 5;

    std::vector<std::string> listOfStrategies_ =
            {"simple"
            };
    std::vector<Player> players_;

    PlayingField playingField_;

    std::map<std::string, MFP> commands_;


    void parseParams();

    void setUpCommands();

    bool setUpGame();

    bool endGame();

    bool continueGame();

public:

    Game(int argc, const char **argv);

    ~Game();

    void run();
};
