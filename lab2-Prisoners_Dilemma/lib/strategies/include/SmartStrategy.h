#pragma once

#include "IStrategy.h"
#include "PlayerChoice.h"

class SmartStrategy : public IStrategy
{
public:
    ~SmartStrategy() override = default;

    PlayerChoice makeMove(std::string &oppMoves) override;
};