#pragma once

#include "Database.h"

class Party
{
private:
	int getHeroPosition();

	Database* database;

public: 
	vector<Hero> PartyMembers;

	Party(vector<int> idHeroes, Database* database);

	void addToParty(int heroId);

	void removeFromParty();
};

