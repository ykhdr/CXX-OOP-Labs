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

    resultMatrix_.setHeight(height);
    resultMatrix_.setWeight(weight);
    resultMatrix_.makeMatrix();
}

PlayingField::~PlayingField()
{

}

std::string PlayingField::getLine(int height)
{
    return moveMatrix_.getLine(height);
}

void PlayingField::makeMoves(std::vector<Player> players, std::string previousMoves, int &currentMove)
{
    for (int i = 0; i < players.size(); ++i)
    {
        moveMatrix_.addMove(i, players[i].makeMove(previousMoves), currentMove);
    }
}

void PlayingField::countResult(const std::string &moves, const int &currentMove)
{
    resultMatrix_.countResult(moves, currentMove);
}

void PlayingField::printGameStatus(int const &currentMove)
{
    for (int i = 0; i < currentMove + 1; ++i)
    {
        std::cout << "\t\t" << moveMatrix_.getLine(i);
        if (i == 0)
        {
            std::cout << "  =>   ";
        } else
        {
            std:: cout << " =>   ";
        }

        std::cout << resultMatrix_.getLine(i) << std::endl;
    }
}










