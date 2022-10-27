#pragma once

#include "IMatrix.h"
#include <memory>
#include <cstring>

class ResultMatrix : private IMatrix
{
    std::vector<std::vector<std::string>> matrix_;

    int weight_ = 3;
    int height_ = 6;

public:
    ResultMatrix() = default;

    ~ResultMatrix() override = default;

    void setWeight(int);

    void setHeight(int);

    std::string getLine(int height) const override;

    void makeMatrix() override;

    void countMoveResult(const std::string &moves, const int &currentMove);

    std::vector<int> countGameResult();
};