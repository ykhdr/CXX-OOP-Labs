#include "PersonStrategy.h"

PlayerChoice PersonStrategy::makeMove(std::string &oppMoves)
{
    std::cout << "\t\t\tMake move:" << std::endl
              << "\t\t\t'C' - to cooperate" << std::endl
              << "\t\t\t'D' - to betray" << std::endl;

    char move;
    while (true)
    {
        std::cin >> move;

        if (move == 'D')
        {
            return PlayerChoice::evBetray;
        }
        if (move == 'C')
        {
            return PlayerChoice::evCooperate;
        }

        std::cout << std::endl
                  << "You entered wrong move, try again" << std::endl;
    }
}