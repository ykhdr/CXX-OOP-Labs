#include "DefaultStrategy.h"

#include "IStrategy.h"

PlayerChoice DefaultStrategy::makeMove(std::string &oppMoves)
{
    // Switch team every round
    isBetrayer = !isBetrayer;
    return !isBetrayer ? PlayerChoice::evCooperate : PlayerChoice::evBetray;
}