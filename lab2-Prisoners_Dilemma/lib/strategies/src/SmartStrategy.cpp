#include "SmartStrategy.h"

#include <algorithm>

PlayerChoice SmartStrategy::makeMove(std::string &oppMoves)
{
    auto employers = std::count(oppMoves.begin(), oppMoves.end(), 'C');
    auto traitors = std::count(oppMoves.begin(), oppMoves.end(), 'D');

    if (traitors < employers)
    {
        return PlayerChoice::evCooperate;
    }

    return PlayerChoice::evBetray;
}