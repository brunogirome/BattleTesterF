#pragma once

#include "Game.h"

class Battle
{
private:
	Party* party;

	vector<Enemy> enemyParty;

	string getLine(int size, string character = "-");

	void drawLine(int size, bool border = false);

public:
	Battle(Game* game, vector<int> enemyPartyIds);

	void battleStart();

	void battleInterface();
};

