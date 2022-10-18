#pragma once

#include <string>

#include "IStrategy.h"
#include "StrategyFactory.h"
#include "../strategies/include/SimpleStrategy.h"



class Player
{

private:
    IStrategy* strategy_ = nullptr;
public:
    Player(std::string);
	~Player();
	bool makeMove(std::vector<std::string_view> moves);
};