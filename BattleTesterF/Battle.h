#pragma once

#include "Game.h"

class Battle
{
private:
	Party* party;

	vector<Enemy> enemyParty;

public:
	Battle(Game* game, vector<int> enemyPartyIds);

	void battleStart();
};

