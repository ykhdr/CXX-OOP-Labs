#pragma once

#include "IGameMode.h"

class FastGameMode : public IGameMode
{
private:
    std::vector<std::shared_ptr<IStrategy>> players_;

    PlayingField playingField_;

    int playersNum_;
    int movesNum_;

public:
    explicit FastGameMode(std::vector<std::shared_ptr<IStrategy>> && players, int &moves);

    ~FastGameMode() override = default;

    void run() override;

};