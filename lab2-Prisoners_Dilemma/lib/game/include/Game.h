#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <ctime>
#include <map>
#include <stdexcept>
#include <functional>

#include "IGameModeCreator.h"


//Имеем gamemode
/*
    В каждом gamemode будет одтельная реализация игры(?)
    Или же в зависимости от gamemode будет происходить игра в game.cpp
    Скорее всего в gamemode 

*/

class Game
{
private:

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

    int argc_;
    std::vector<std::string> argv_;

    std::unique_ptr<ParsingCommandLineArgs> parsing_ = std::make_unique<ParsingCommandLineArgs>();

    std::string_view gameModeName_;
    std::unique_ptr<IGameMode> gameMode_ = nullptr;

    int numOfMoves_ = 5;

public:

    Game(int argc, const char **argv);

    ~Game();

    void run();
};


