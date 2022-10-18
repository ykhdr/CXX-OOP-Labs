#pragma once

#include "Matrix.h"
#include <string>


class MoveMatrix //: private Matrix
{
private:
    std::string** matrix_;

    int weight_ = 3;
    int height_ = 6;

public:
	MoveMatrix();
    MoveMatrix(int weight, int height);
	~MoveMatrix();// override;

    //std::vector<std::string_view> getLine(int height) const override;
    void makeMatrix();// override;

};