#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <stdexcept>
#include <unordered_map>
#include <functional>

#include "Player.h"
#include "PlayingField.h"
#include "FastGameMod.h"
#include "MoveMatrix.h"
#include "TournamentGameMod.h"
#include "DetailedGameMod.h"
#include "StrategyFactory.h"
#include "../strategies/include/SimpleStrategy.h"

typedef void (*voidFunctionType)();

class Game
{
private:
	int argc_;
	std::vector<std::string> argv_;

    MoveMatrix moveMatrix_;
    //ResultMatrix resultMatrix_;
    std::map<std::string, std::function<bool()>> commands_;

    void setUpCommands();

    friend bool setUpGame();
    friend bool endGame();
    friend bool continueGame();

public:
	Game(int argc, const char** argv);
	~Game();
	
	void run();
};