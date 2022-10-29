#pragma once

#include <iostream>

#include "MoveMatrix.h"
#include "ResultMatrix.h"
#include "StrategyFactory.h"

class PlayingField
{
private:

    ResultMatrix resultMatrix_;
    MoveMatrix moveMatrix_;

public:
    PlayingField() = default;

    PlayingField(int height, int weight);

    ~PlayingField();

    std::string getLine(int);

    void makeMoves(std::vector<std::shared_ptr<IStrategy>> players, std::string previousMoves, int &currentMove);

    void countResult(const std::string &moves, const int &currentMove);

    void printGameStatus(const int &currentMove);

    void printGameResult();
};