#pragma once

#include "IStrategy.h"
#include "Factory.h"

#include <iostream>

class SimpleStrategy : public IStrategy
{
public:
	bool makeMove(const std::vector<std::string_view> &oppMoves) override;

};

class SimpleStrategyFactory : public Factory
{
public:
	std::unique_ptr<IStrategy> create() override;
};