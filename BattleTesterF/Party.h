#pragma once

#include "Database.h"

class Party
{
private:
	int getHeroPosition();

	Database* database;

public: 
	std::vector<Hero> PartyMembers;

	Party(std::vector<int> idHeroes, Database* database);

	void addToParty(int heroId);

	void removeFromParty();
};

