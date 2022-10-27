#include "Player.h"

Player::Player(const std::string& strategyName)
{
    Factory *factory = &Factory::getInstance();

    strategy_ = factory->create(strategyName);
}

Player::~Player()
{
}

bool Player::makeMove(std::string &moves)
{
    return strategy_->makeMove(moves);
}
