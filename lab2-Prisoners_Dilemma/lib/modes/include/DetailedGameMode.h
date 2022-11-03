#pragma once

#include "IGameMode.h"

class DetailedGameMode : public IGameMode
{
private:
    typedef bool (DetailedGameMode::*pGameModeFun)();

    std::map<std::string, pGameModeFun> commandMap_;

    bool isGameStarted_ = false;

    std::vector<std::shared_ptr<IStrategy>> players_;

    PlayingField playingField_;

    int playersNum_;
    int movesNum_;
    int currentMove_;

    bool setUpGame();

    bool continueGame();

    bool endGame();

public:
    explicit DetailedGameMode(std::vector<std::shared_ptr<IStrategy>> &&players, int &moves);

    ~DetailedGameMode() override = default;

    void run() override;




};