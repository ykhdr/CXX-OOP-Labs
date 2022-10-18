#include "Game.h"

int main(int argc, char const *argv[])
{
    Game game = Game(argc,argv);
    game.run();
	return 0;
}