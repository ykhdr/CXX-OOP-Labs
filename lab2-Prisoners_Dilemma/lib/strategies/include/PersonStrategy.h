#pragma once

#include <iostream>

#include "IStrategy.h"

class PersonStrategy : public IStrategy
{
public:
    bool makeMove(std::string &oppMoves) override; 
};

