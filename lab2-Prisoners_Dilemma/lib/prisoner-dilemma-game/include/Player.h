#pragma once

#include <string>

#include "IStrategy.h"
#include "../strategies/include/SimpleStrategy.h"

#include "Factory.h"


//TODO: мб избавиться от этого класса, так как он не несет в себе по сути никакого смысла
class Player
{

private:
    std::shared_ptr<IStrategy> strategy_;
public:
    Player(const std::string&);
    ~Player();
    bool makeMove(std::string &moves);
};