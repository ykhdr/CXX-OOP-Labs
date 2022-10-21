#pragma once

#include "IMatrix.h"

class MoveMatrix : private IMatrix
{
private:
    std::vector<std::vector<std::string>> matrix_;

    int weight_ = 3;
    int height_ = 6;

public:
    MoveMatrix() = default;

    ~MoveMatrix() override;

    void setWeight(int);

    void setHeight(int);

    std::string getLine(int height) const override;

    void makeMatrix() override;

    void addMove(int numOfPlayer, bool moveChoice, const int &currentMove);
};