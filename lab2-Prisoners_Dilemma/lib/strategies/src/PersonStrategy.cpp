#include "PersonStrategy.h"

bool PersonStrategy::makeMove(std::string &oppMoves)
{
    std::cout << "\t\t\tMake move ('C' or 'D'): ";
    
    char move;
    while(true){
        std::cin >> move;

        if(move=='D')
        {
            return true;
        }
        if(move == 'C')
        {
            return false;
        }
        
        std::cout << std::endl << "You entered wrong move, try again" << std::endl;
    }   
}