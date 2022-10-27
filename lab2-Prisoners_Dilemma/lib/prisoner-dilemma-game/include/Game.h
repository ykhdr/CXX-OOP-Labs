#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <stdexcept>
#include <functional>

#include "Player.h"
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


class ParsingCommandLineArgs;

class Game
{
private:
    typedef bool (Game::*gameFun)();

    bool isGameStarted_ = false;

    int argc_;
    std::vector<std::string> argv_;
    friend ParsingCommandLineArgs;

    std::unique_ptr<ParsingCommandLineArgs> parsing = std::make_unique<ParsingCommandLineArgs>();

    int numOfPrisoners = 3;
    int numOfMoves_ = 6;

    int currentMove_ = 1;

    std::vector<std::string> strategiesList_ =
    {   "simple", "default", "random"
    };

    std::vector<Player> players_;

    PlayingField playingField_;

    std::map<std::string, gameFun> commandList_;

    bool setUpGame();

    bool endGame();

    bool continueGame();

public:

    Game(int argc, const char **argv);

    ~Game();

    void run();
};
