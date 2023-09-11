#pragma once

#include <vector>

#include "Hero.h"
#include "Database.h"

class Party
{
private:
	Database* database;

	int getHeroPosition();

public: 
	vector<Hero> partyMembers;

	Party(vector<int> idHeroes, Database* gameDatabase);

	void addToParty(int heroId);

	void removeFromParty();
};

