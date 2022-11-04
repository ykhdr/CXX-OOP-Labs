#pragma once

#include "IMatrix.h"

class MoveMatrix : private IMatrix
{
private:
    std::vector<std::vector<std::string>> matrix_;

    static constexpr int weight_ = 3;

    int height_ = 6;

public:
    MoveMatrix() = default;

    explicit MoveMatrix(int height);

    ~MoveMatrix() override;

    std::string getLine(int height) const override;

    void addMove(int numOfPlayer, bool moveChoice, const int &currentMove);
};