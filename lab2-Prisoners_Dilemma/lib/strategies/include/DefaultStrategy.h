#pragma once

#include "IStrategy.h"
#include "PlayerChoice.h"

class DefaultStrategy : public IStrategy
{
private:
    bool isBetrayer = false;

public:
    PlayerChoice makeMove(std::string &oppMoves) override;
};
