#pragma once

#include "Matrix.h"
#include <string>


class MoveMatrix : private Matrix
{
private:
    std::vector<std::vector<std::string>> matrix_;

    int weight_ = 3;
    int height_ = 6;

    int numOfMove_ = 1;
public:
	MoveMatrix() = default;
    MoveMatrix(int weight, int height);
	~MoveMatrix() override;

    void setWeight(int);
    void setHeight(int);

    std::vector<std::string_view> getLine(int height) const;
    void makeMatrix() override;
    void addMove(int numOfPlayer,bool moveChoice);
};