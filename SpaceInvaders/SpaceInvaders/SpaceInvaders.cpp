// SpaceInvaders.cpp : Defines the entry point for the console application.
//

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "GameManager.h"

int WinMain(int argc, char** argv)
{
	game::GameManager::instance().configure_game();
	game::GameManager::instance().game_loop();

	return 0;
}
