#pragma once

#include "Game.h"
#include "IGameMode.h"

class TournamentGame : public IGameMode
{
private:
    Game game_;

    std::vector<std::string> strategiesNames_; 

    int moves_;

public:
    TournamentGame(std::vector<std::string> strategiesNames, int &moves);
    
    ~TournamentGame() override = default;

    void run() override;
};
