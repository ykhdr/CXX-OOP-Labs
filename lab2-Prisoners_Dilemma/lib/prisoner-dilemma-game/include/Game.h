#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <stdexcept>
#include <functional>

#include "PlayingField.h"
#include "MoveMatrix.h"
#include "Factory.h"
#include "ParsingCommandLineArgs.h"

#include "../game-mode/include/FastGameMode.h"
#include "../game-mode/include/TournamentGameMode.h"
#include "../game-mode/include/DetailedGameMode.h"

#include "../strategies/include/SimpleStrategy.h"
#include "../strategies/include/DefaultStrategy.h"
#include "../strategies/include/RandomStrategy.h"
#include "../strategies/include/SmartStrategy.h"

class ParsingCommandLineArgs;

class Game
{
private:
    typedef bool (Game::*pGameFun)();

    friend ParsingCommandLineArgs;

    bool isGameStarted_ = false;

    int argc_;
    std::vector<std::string> argv_;

    std::unique_ptr<ParsingCommandLineArgs> parsing = std::make_unique<ParsingCommandLineArgs>();

    int numOfPrisoners = 3;
    int numOfMoves_ = 5;

    int currentMove_ = 1;

    std::vector<std::shared_ptr<IStrategy>> players_;

    PlayingField playingField_;

    std::map<std::string, pGameFun> commandMap_;

    bool setUpGame();

    bool endGame();

    bool continueGame();

public:

    Game(int argc, const char **argv);

    ~Game();

    void run();
};
