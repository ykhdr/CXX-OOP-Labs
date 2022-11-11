#pragma once

#include "IStrategy.h"
#include "PlayerChoice.h"

class RandomStrategy : public IStrategy
{
public:
    RandomStrategy();
    PlayerChoice makeMove(std::string &oppMoves) override;
};