#pragma once

#include <vector>

class IStrategy
{
private:
	
public:
	virtual ~IStrategy() {}

	virtual bool makeMove(const std::vector<char> &oppMoves) = 0;

};