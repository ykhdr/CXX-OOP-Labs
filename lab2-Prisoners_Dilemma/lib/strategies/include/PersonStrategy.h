#pragma once

#include <iostream>

#include "IStrategy.h"

class PersonStrategy : public IStrategy
{
public:
    PlayerChoice makeMove(std::string &oppMoves) override;
};