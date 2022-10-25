#pragma once

#include "IStrategy.h"

#include <iostream>

class SimpleStrategy : public IStrategy
{
public:
	bool makeMove(std::string& oppMoves) override;
};
