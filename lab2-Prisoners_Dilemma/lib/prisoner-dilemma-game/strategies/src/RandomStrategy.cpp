
#include "../include/RandomStrategy.h"

bool RandomStrategy::makeMove(std::string &oppMoves)
{
    srand(time(nullptr));

    return ((1 + rand()) % 2);
}

