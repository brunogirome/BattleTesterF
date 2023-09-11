#pragma once

#include<windows.h>
#include <chrono>
#include <thread>

#include "Party.h"
#include "Database.h"

class Game
{
public:
	Party * GameParty;

	Database* GameDatabase;

	Game();

	void init();
};

