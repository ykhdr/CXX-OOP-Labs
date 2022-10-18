#include <iostream>
#include "MoveMatrix.h"




MoveMatrix::MoveMatrix(int weight, int height) : weight_(weight), height_(height) {}

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

MoveMatrix::~MoveMatrix()
{
    
}

std::vector<std::string_view> MoveMatrix::getLine(int height) const
{
    std::string str;
    for (int i = 0; i < weight_; ++i)
    {
        str+=matrix_[height][i];
        str+=" ";
    }

    std::vector<std::string_view> v;

    for (int i = 0; i < weight_; ++i)
    {
        v.emplace_back(matrix_[height][i]);
    }

    return v;
}

void MoveMatrix::setWeight(int weight)
{
    this->weight_ = weight;
}

void MoveMatrix::setHeight(int height)
{
    this->height_ = height;
}



void MoveMatrix::addMove(int numOfPlayer,bool moveChoice)
{
    moveChoice ? matrix_[numOfMove_][numOfPlayer] = "D" : matrix_[numOfMove_][numOfPlayer] = "C";

    if(numOfPlayer == weight_)
    {
        ++numOfMove_;
    }
}






