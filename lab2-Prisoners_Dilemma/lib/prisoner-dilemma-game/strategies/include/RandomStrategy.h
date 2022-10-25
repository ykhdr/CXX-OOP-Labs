#pragma once

#include <random>

#include "IStrategy.h"
class RandomStrategy : public IStrategy
{

public:
    bool makeMove(std::string &oppMoves) override;
};


