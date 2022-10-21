#include "MoveMatrix.h"

void MoveMatrix::makeMatrix()
{
    matrix_.resize(height_);
    for (int i = 0; i < height_; ++i)
    {
        matrix_[i].resize(weight_);
    }

    for (int i = 0; i < weight_; ++i)
    {
        matrix_[0][i] = "Pr" + std::to_string(i+1);
    }
}

MoveMatrix::~MoveMatrix() {}

std::string MoveMatrix::getLine(int height) const
{
    std::string str;
    if(height!=0)
        str+=" ";

    for (int i = 0; i < weight_; ++i)
    {
        str+=matrix_[height][i];
        height==0 ? str+=" " : str+= "   ";
    }

    return str;
}

void MoveMatrix::setWeight(int weight)
{
    this->weight_ = weight;
}

void MoveMatrix::setHeight(int height)
{
    this->height_ = height;
}

void MoveMatrix::addMove(int numOfPlayer,bool moveChoice, const int &currentMove)
{
    moveChoice ? matrix_[currentMove][numOfPlayer] = "D" : matrix_[currentMove][numOfPlayer] = "C";

}








