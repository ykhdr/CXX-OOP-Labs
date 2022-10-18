#include "../include/SimpleStrategy.h"



bool SimpleStrategy::makeMove(const std::vector<char> &oppMoves)
{
	bool isBetray = false;
	for(auto el : oppMoves)
	{
		if(el=='D')
		{
			isBetray = true;
			break;
		}
	}

	return isBetray;
}

std::unique_ptr<IStrategy> SimpleStrategyFactory::create()
{
	return std::make_unique<SimpleStrategy>();
}