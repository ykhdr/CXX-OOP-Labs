#include "../include/SimpleStrategy.h"


bool SimpleStrategy::makeMove(std::string &oppMoves)
{
    if(true)
    {
        return ((1 + std::rand()) % 2);
    }

    if (oppMoves[0]=='1')
    {
        return ((1 + std::rand()) % 2);
    }

    bool isBetray = false;

    for (auto oppMove: oppMoves)
    {
        if (oppMove == 'D')
        {
            isBetray = true;
            break;
        }
    }

    return isBetray;
}

//std::unique_ptr<IStrategy> SimpleStrategyFactory::create()
//{
//    //return std::make_unique<SimpleStrategy>();
//}