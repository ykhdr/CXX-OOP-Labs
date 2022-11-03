#include "FastGameMode.h"

FastGameMode::FastGameMode(std::vector<std::shared_ptr<IStrategy>> &&players, int &moves) :
        players_(players), movesNum_(moves)
{
    playersNum_ = players.size();
    playingField_ = PlayingField(movesNum_ + 1, playersNum_);

}

void FastGameMode::run()
{
    for (int currentMove = 1; currentMove <= movesNum_; ++currentMove)
    {
        if(currentMove == 1)
        {
            playingField_.makeMoves(players_, "1", currentMove);
        }
        else
        {
            playingField_.makeMoves(players_, playingField_.getLine(currentMove - 1), currentMove);
        }
        playingField_.countMoveResult(playingField_.getLine(currentMove), currentMove);
    }

    playingField_.printGameResult();
}


