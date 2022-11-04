#include "TournamentGameMode.h"

namespace
{
    int findIdMax(std::vector<int> v)
    {
        int idMax = 0;

        for (int i = 0; i < v.size() - 1; ++i)
        {
            if (v[idMax] < v[i + 1])
            {
                idMax = i + 1;
            }
        }

        return idMax;
    }
}

TournamentGameMode::TournamentGameMode(std::vector<std::shared_ptr<IStrategy>> &&players, int &moves) :
        players_(players), movesNum_(moves)
{
    playingField_ = PlayingField(movesNum_ + 1);
}

TournamentGameMode::~TournamentGameMode()
= default;

void TournamentGameMode::run()
{
    int gameCounter = 1;

    int maxValue = 0;

    for (auto itFirst = players_.begin(); itFirst != std::prev(players_.end(), 2); ++itFirst)
    {
        for (auto itSecond = std::next(itFirst); itSecond != std::prev(players_.end()); ++itSecond)
        {
            for (auto itThird = std::next(itSecond); itThird != players_.end(); ++itThird)
            {
                std::cout << "\n\t\t\tGame " << gameCounter << " started\n" << std::endl;
                std::cout << "\t\tPlayers " << itFirst - players_.begin() + 1
                          << ", " << itSecond - players_.begin() + 1
                          << ", " << itThird - players_.begin() + 1
                          << " are playing now"<<std::endl;

                ++gameCounter;

                std::vector<std::shared_ptr<IStrategy>> pl;

                pl.push_back(*itFirst);
                pl.push_back(*itSecond);
                pl.push_back(*itThird);

                for (int currentMove = 1; currentMove <= movesNum_; ++currentMove)
                {
                    if (currentMove == 1)
                    {
                        playingField_.makeMoves(pl, "1", currentMove);
                    } else
                    {
                        playingField_.makeMoves(pl, playingField_.getLine(currentMove - 1), currentMove);
                    }

                    playingField_.countMoveResult(playingField_.getLine(currentMove), currentMove);
                }

                std::vector<int> gameResult = playingField_.countGameResult();

                playingField_.printGameResult();

                int idMax = findIdMax(gameResult);

                if (gameResult[idMax] > maxValue)
                {
                    maxValue = gameResult[idMax];
                }

                int idPlayer = 0;

                for (int i = 0; i < gameResult.size(); ++i)
                {
                    if (gameResult[i] != gameResult[idMax])
                    {
                        continue;
                    }

                    switch (i)
                    {
                        case 0:
                            idPlayer = itFirst - players_.begin();
                            break;
                        case 1:
                            idPlayer = itSecond - players_.begin();
                            break;
                        case 2:
                            idPlayer = itThird - players_.begin();
                            break;
                        default:
                            break;
                    }

                    auto key = resultMap_.find(idPlayer);

                    if (key == resultMap_.end())
                    {
                        resultMap_.insert(std::make_pair(idPlayer, gameResult[idMax]));
                        continue;
                    }

                    if (gameResult[idMax] > key->second)
                    {
                        resultMap_[key->first] = gameResult[idMax];
                    }

                }
            }
        }
    }

    printResult(maxValue);
}


void TournamentGameMode::printResult(int maxValue)
{
    std::cout << "\t\t The Winner of tournament is";

    bool isFisrt = true;
    for (const auto &result: resultMap_)
    {
        if (result.second == maxValue)
        {

            if (!isFisrt)
            {
                std::cout << ",";
            }
            std::cout << " " << result.first + 1;
            isFisrt = false;
        }
    }

    std::cout << " with score " << maxValue << "!" << std::endl;
}