#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <stdexcept>
#include <functional>

#include "PlayingField.h"
#include "StrategyFactory.h"
#include "GameMod.h"

class Game
{
private:
    typedef bool (Game::*pGameFun)();

    class ParsingCommandLineArgs
    {
        enum StringValue
        {
            evMode,
            evSteps
        };

        std::map<std::string_view, StringValue> stringValuesMap_;

        void initialize(Game &);

        bool parseCommand(Game &game, std::string &str);

    public:
        ParsingCommandLineArgs() = default;

        bool parseLine(Game &);

    };

    bool isGameStarted_ = false;

    int argc_;
    std::vector<std::string> argv_;

    std::unique_ptr<ParsingCommandLineArgs> parsing_ = std::make_unique<ParsingCommandLineArgs>();

    int numOfPrisoners_ = 3;
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


