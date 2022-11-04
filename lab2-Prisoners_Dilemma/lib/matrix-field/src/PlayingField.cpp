#include "../include/PlayingField.h"

namespace
{
    int findIdMax(std::vector<int> v)
    {
        int idMax = 0;

        for (int i = 0; i < v.size() - 1; ++i)
        {
            if (v[idMax] < v[i + 1])
            {
                idMax = i + 1;
            }
        }

        return idMax;
    }
}

PlayingField::PlayingField(int height)
{
    moveMatrix_ = MoveMatrix(height);
    resultMatrix_ = ResultMatrix(height);
}

PlayingField::~PlayingField()
{
}

std::string PlayingField::getLine(int height)
{
    return moveMatrix_.getLine(height);
}

void PlayingField::makeMoves
        (std::vector<std::shared_ptr<IStrategy>> players, std::string previousMoves, int &currentMove)
{
    for (int i = 0; i < players.size(); ++i)
    {
        moveMatrix_.addMove(i, players[i]->makeMove(previousMoves), currentMove);
    }
}

void PlayingField::countMoveResult(const std::string &moves, const int &currentMove)
{
    resultMatrix_.countMoveResult(moves, currentMove);
}

std::vector<int> PlayingField::countGameResult()
{
    return resultMatrix_.countGameResult();
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
            std::cout << " =>   ";
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

    for (int el: result)
    {
        std::cout << el << "  ";
    }

    std::cout << std::endl;

    int id = findIdMax(result);

    std::cout << "\n\t\t   The Winners: "; //<< id + 1 << "!" << std::endl;
    for (int i = 0; i < result.size(); ++i)
    {
        if (result[i] == result[id])
        {
            if (i == id)
            {
                std::cout << i + 1;
            } else
            {
                std::cout << ", " << i + 1;
            }

        }
    }
    std::cout <<" with score " << result[id] << "!\n" << std::endl;
}