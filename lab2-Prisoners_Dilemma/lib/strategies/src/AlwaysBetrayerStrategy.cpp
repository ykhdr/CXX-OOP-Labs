#include "AlwaysBetrayerStrategy.h"

PlayerChoice AlwaysBetrayerStrategy::makeMove()
{
    return PlayerChoice::evBetray;
}

void AlwaysBetrayerStrategy::opponentsMoves(PlayerChoice opponent1Move, PlayerChoice opponent2Move)
{}