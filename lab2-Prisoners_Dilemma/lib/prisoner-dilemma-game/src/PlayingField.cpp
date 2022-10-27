#include "PlayingField.h"

namespace
{
    int findIdMax(std::vector<int> v)
    {
        int idMax = 0;

        for (int i = 0; i < v.size()-1; ++i)
        {
            if(v[i] < v[i+1])
            {
                idMax = i+1;
            }
        }

        return idMax;
    }
}


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
    resultMatrix_.countMoveResult(moves, currentMove);
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

void PlayingField::printGameResult()
{
    std::cout << "\t\t\tGame result:" << std::endl;
    std::cout << "\t\t" << resultMatrix_.getLine(0) << std::endl;

    std::vector<int> result = resultMatrix_.countGameResult();
    std::cout << "\t\t ";

    for(int el : result)
    {
        std::cout << el << "  ";
    }

    std::cout << std::endl;

    int id = findIdMax(result);

    std::cout << "\n\t\t   The Winner is Prisoner " << id+1 << "!" << std::endl;
}










