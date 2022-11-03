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
    playingField_ = PlayingField(movesNum_ + 1, 3);
}

TournamentGameMode::~TournamentGameMode()
= default;

void TournamentGameMode::run()
{
    for (auto itFirst = players_.begin(); itFirst != std::prev(players_.end(), 2); ++itFirst)
    {
        for (auto itSecond = std::next(itFirst); itSecond != std::prev(players_.end()); ++itSecond)
        {
            for (auto itThird = std::next(itSecond); itThird != players_.end(); ++itThird)
            {
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

                std::vector<int> result = playingField_.countGameResult();

                //TODO: сделать так, чтобы в мапу мы записывали номер ИГРОКА с его результатом, желательно, чтобы можно было переписать значение по известному ключу

                int idMax = findIdMax(result);

                int idPlayer;
                switch (idMax)
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
                //TODO: сделать поиск по ключу, если уже имеется, то сравниваем значения и в случае, если новое значение больше предыдущего, то удаляем ту пару и заменяем новой
                resultMap_.insert(std::make_pair(idPlayer, result[idMax]));
            }
        }
    }


}











