#include "PlayingField.h"

PlayingField::PlayingField()
{
    moveMatrix_.makeMatrix();
}

PlayingField::PlayingField(int height, int weight) : height_(height), weight_(weight)
{
    moveMatrix_.setHeight(height);
    moveMatrix_.setWeight(weight);
    moveMatrix_.makeMatrix();
}

PlayingField::~PlayingField()
{

}

std::vector<std::string_view> PlayingField::getLine(int height)
{
    return moveMatrix_.getLine(height);
}




