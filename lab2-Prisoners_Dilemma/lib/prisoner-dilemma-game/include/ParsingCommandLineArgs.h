#pragma once

#include <map>
#include <string>
#include <string_view>
#include "Game.h"

class Game;

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
