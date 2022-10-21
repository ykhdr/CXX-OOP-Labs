#include "ResultMatrix.h"

//ResultMatrix::~ResultMatrix() {}

void ResultMatrix::setWeight(int weight)
{
    weight_ = weight;
}

void ResultMatrix::setHeight(int height)
{
    height_ = height;
}

std::string ResultMatrix::getLine(int height) const
{
    std::string str;
    if (height != 0)
        str += " ";

    for (int i = 0; i < weight_; ++i)
    {
        str += matrix_[height][i];
        height == 0 ? str += " " : str += "   ";
    }

    return str;
}

void ResultMatrix::makeMatrix()
{
    matrix_.resize(height_);
    for (int i = 0; i < height_; ++i)
    {
        matrix_[i].resize(weight_);
    }

    for (int i = 0; i < weight_; ++i)
    {
        matrix_[0][i] = "Pr" + std::to_string(i + 1);
    }
}

void ResultMatrix::countResult(const std::string &moves, const int &currentMove)
{
    int traitors = 0;
    int employers = 0;

    int trPoints = 0;
    int emPoints = 0;

    for (char move: moves)
    {
        if (move == ' ')
        {
            continue;
        }

        move == 'D' ? ++traitors : ++employers;
    }

    if (employers == 0)
    {
        trPoints = 1;
    } else if (traitors == 0)
    {
        emPoints = 2 * employers + 1;
    } else if (employers == 1)
    {
        trPoints = 3 + traitors;
    } else
    {
        trPoints = (2 + employers) * employers;
        emPoints = 1 + employers;
    }

    for (int i = 0, j = 0; i < weight_; ++j)
    {
        if (moves[j] == ' ')
        {
            continue;
        }
        moves[j] == 'C' ?
                matrix_[currentMove][i] = std::to_string(emPoints) : matrix_[currentMove][i] = std::to_string(trPoints);
        ++i;
    }
}


