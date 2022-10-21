#pragma once

#include <vector>
#include <string_view>

class IStrategy
{
private:
	
public:
	virtual ~IStrategy() {}

	virtual bool makeMove(std::string &oppMoves) = 0;

};