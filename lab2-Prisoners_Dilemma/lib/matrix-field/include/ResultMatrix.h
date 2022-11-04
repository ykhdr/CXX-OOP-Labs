#pragma once

#include "IMatrix.h"
#include <memory>
#include <cstring>

class ResultMatrix : private IMatrix
{
    std::vector<std::vector<std::string>> matrix_;

    static constexpr int weight_ = 3;
    int height_ = 6;

public:
    ResultMatrix() = default;

    explicit ResultMatrix(int height);

    ~ResultMatrix() override = default;

    std::string getLine(int height) const override;

    void countMoveResult(const std::string &moves, const int &currentMove);

    std::vector<int> countGameResult();
};