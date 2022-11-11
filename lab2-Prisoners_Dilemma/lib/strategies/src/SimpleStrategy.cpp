#include "SimpleStrategy.h"

PlayerChoice SimpleStrategy::makeMove(std::string &oppMoves)
{
    // Always employer
    return PlayerChoice::evBetray;
}