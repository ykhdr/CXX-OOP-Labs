#pragma once

#include "IStrategy.h"

class DefaultStrategy : public IStrategy
{
private:
    bool isTraitor = false;
public:
    bool makeMove(std::string &oppMoves) override;
};
