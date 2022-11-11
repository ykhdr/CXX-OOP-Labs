#pragma once

#include <vector>
#include <string>

#include "PlayerChoice.h"

class IStrategy
{
public:
	virtual ~IStrategy() = default;

	virtual PlayerChoice makeMove(std::string &oppMoves) = 0;
};