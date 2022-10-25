#pragma once

#include <string>

#include "IStrategy.h"
#include "../strategies/include/SimpleStrategy.h"

#include "Factory.h"

class Player
{

private:
    //IStrategy* strategy_ = nullptr;
    std::shared_ptr<IStrategy> strategy_;
public:
    Player(const std::string&);
	~Player();
	bool makeMove(std::string &moves);
};