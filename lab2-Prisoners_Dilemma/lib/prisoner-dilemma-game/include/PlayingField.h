#pragma once

#include <iostream>

#include "MoveMatrix.h"
#include "ResultMatrix.h"
#include "Player.h"

class PlayingField
{
private:
    int weight_ = 3;
    int height_ = 6;

    ResultMatrix resultMatrix_;
    MoveMatrix moveMatrix_;

public:
	PlayingField();
    PlayingField(int height,int weight);
	~PlayingField();

    std::string getLine(int);


    void makeMoves(std::vector<Player> players, std::string previousMoves, int &currentMove);
    void countResult(const std::string& moves, const int &currentMove);
    void printGameStatus(const int &currentMove);
    void printGameResult();
};