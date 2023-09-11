#pragma once

#include "Party.h"

class Game
{
private:

	Database* database;
public:
	Party* party;

	Game();

	void init();

	void end();
};

