#pragma once

#include <vector>
#include <string>

class IStrategy
{
public:
	virtual ~IStrategy() = default;

	virtual bool makeMove(std::string &oppMoves) = 0;

};