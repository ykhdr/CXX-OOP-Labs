#include "TournamentGame.h"

#include "FastGame.h"

TournamentGame::TournamentGame(std::vector<std::string> strategiesNames, int &moves) : strategiesNames_(std::move(strategiesNames)), moves_(moves) {}

void TournamentGame::run()
{
    for (auto itFirst = strategiesNames_.begin(); itFirst != std::prev(strategiesNames_.end(), 2); ++itFirst)
    {
        for (auto itSecond = std::next(itFirst); itSecond != std::prev(strategiesNames_.end()); ++itSecond)
        {
            for (auto itThird = std::next(itSecond); itThird != strategiesNames_.end(); ++itThird)
            {
                std::vector<std::string> playersNames;

                playersNames.push_back(*itFirst);
                playersNames.push_back(*itSecond);
                playersNames.push_back(*itThird);

                FastGame game = FastGame(playersNames, moves_);
                game.run();
                //TODO: вывести победителя
                // сделать в fastgame метод который выводит победителя? в целом можно, но хз 
            }
        }
    }
}