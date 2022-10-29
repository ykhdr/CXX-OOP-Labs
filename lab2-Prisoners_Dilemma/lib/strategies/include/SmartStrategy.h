#pragma once

#include "IStrategy.h"
#include <algorithm>

class SmartStrategy : public IStrategy
{
public:
    ~SmartStrategy() override = default;

    bool makeMove(std::string &oppMoves) override;

};



