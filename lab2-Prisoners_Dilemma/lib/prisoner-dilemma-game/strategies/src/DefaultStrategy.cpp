//
// Created by User on 22.10.2022.
//
#include "../strategies/include/DefaultStrategy.h"

#include "IStrategy.h"

bool DefaultStrategy::makeMove(std::string &oppMoves)
{
    // Switch team every round
    return isTraitor = !isTraitor;
}
