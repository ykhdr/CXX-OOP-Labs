#pragma once

#include <iostream>

#include "MoveMatrix.h"
#include "ResultMatrix.h"

class PlayingField
{
private:
    int weight_ = 3;
    int height_ = 6;


    //ResultMatrix resultMatrix_;

public:
	PlayingField();
    PlayingField(int,int);
	~PlayingField();

    MoveMatrix moveMatrix_;

    std::vector<std::string_view> getLine(int);


};