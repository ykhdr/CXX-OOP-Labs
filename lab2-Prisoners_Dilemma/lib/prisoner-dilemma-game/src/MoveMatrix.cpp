#include <iostream>
#include "MoveMatrix.h"



MoveMatrix::MoveMatrix()
{
    matrix_ = new std::string* [height_];
    for (int i = 0; i < height_; ++i)
    {
        matrix_[i] = new std::string [weight_];
    }
}

MoveMatrix::MoveMatrix(int weight, int height) : weight_(weight), height_(height)
{
    matrix_ = new std::string* [height];
    for (int i = 0; i < height; ++i)
    {
        matrix_[i] = new std::string [weight];
    }

}

void MoveMatrix::makeMatrix()
{
    for (int i = 0; i < height_; ++i)
    {
        for (int j = 0; j < weight_; ++j)
        {
            matrix_[i][j] = "as ";
        }
    }
    for (int i = 0; i < height_; ++i)
    {
        for (int j = 0; j < weight_; ++j)
        {
            std::cout << matrix_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

MoveMatrix::~MoveMatrix()
{
    for (int i = 0; i < height_; ++i)
    {
        delete [] matrix_[i];
    }
    //delete [] matrix_;
}

//std::vector<std::string_view> MoveMatrix::getLine(int height) const
//{
//
//}




