#include "RandomStrategy.h"

#include <random>
#include <ctime>

RandomStrategy::RandomStrategy()
{
    srand(time(NULL));
}

PlayerChoice RandomStrategy::makeMove(std::string &oppMoves)
{
    return rand() % 2 == 0 ? PlayerChoice::evCooperate : PlayerChoice::evBetray;
}