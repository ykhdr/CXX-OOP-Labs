#pragma once

#include "IGameMode.h"

class TournamentGameMode : public IGameMode
{
private:
    std::vector<std::shared_ptr<IStrategy>> players_;

    std::map<int,int> resultMap_;

    int movesNum_;

    PlayingField playingField_;

public:
    explicit TournamentGameMode(std::vector<std::shared_ptr<IStrategy>> && players, int &moves);

    ~TournamentGameMode() override;

    void run() override;

};