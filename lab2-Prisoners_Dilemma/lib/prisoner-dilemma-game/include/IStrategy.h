#pragma once

#include <vector>
#include <string_view>

class IStrategy
{
private:
	
public:
	virtual ~IStrategy() {}

	virtual bool makeMove(const std::vector<std::string_view> &oppMoves) = 0;

};