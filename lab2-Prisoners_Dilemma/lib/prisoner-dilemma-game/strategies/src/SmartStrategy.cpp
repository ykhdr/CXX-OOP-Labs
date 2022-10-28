#include "SmartStrategy.h"

bool SmartStrategy::makeMove(std::string &oppMoves)
{
    auto employers = std::count(oppMoves.begin(), oppMoves.end(), 'C');
    auto traitors = std::count(oppMoves.begin(), oppMoves.end(), 'D');

    if (traitors < employers)
    {
        return false;
    }

    return true;
}