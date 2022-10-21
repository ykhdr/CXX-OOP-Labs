#include "Player.h"

Player::Player(std::string)
{
//TODO: реализовать через фабрику стратегий
    //SimpleStrategy obj;
    //strategy_ = &obj;

}

Player::~Player()
{
    //strategy_ = nullptr;
}

bool Player::makeMove(std::string &moves)
{

    return strategy_.makeMove(moves); //TODO: пофиксить какую то ошибку здесь
}
