#include "Game.h"

int main(int argc, char** argv)
{
	Game* game = new Game();

	if (game->Initialize())
	{
		game->Run();
	}

	game->Exit();

	return 0;
}