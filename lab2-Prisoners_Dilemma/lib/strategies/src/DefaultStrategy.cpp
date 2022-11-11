#include "DefaultStrategy.h"

#include "IStrategy.h"

PlayerChoice DefaultStrategy::makeMove(std::string &oppMoves)
{
    // Switch team every round
    isBetrayer_ = !isBetrayer_;
    return !isBetrayer_ ? PlayerChoice::evCooperate : PlayerChoice::evBetray;
}