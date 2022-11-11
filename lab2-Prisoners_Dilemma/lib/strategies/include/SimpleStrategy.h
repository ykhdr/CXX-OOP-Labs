#pragma once

#include "IStrategy.h"
#include "PlayerChoice.h"

class SimpleStrategy : public IStrategy
{
public:
	PlayerChoice makeMove(std::string& oppMoves) override;
};