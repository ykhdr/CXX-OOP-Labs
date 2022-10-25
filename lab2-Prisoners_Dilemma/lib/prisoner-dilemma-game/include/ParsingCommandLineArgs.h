#pragma once

#include <map>
#include <string>
#include <string_view>
#include "Game.h"

class Game;

class ParsingCommandLineArgs
{
    enum StringValue{
        evNotDefined,
        evMode,
        evSteps
    };

    void initialize(Game&);

    std::map<std::string_view, StringValue> stringValuesMap_;
public:
    ParsingCommandLineArgs();

    void parseLine(Game &);

};
