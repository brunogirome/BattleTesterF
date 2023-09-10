#pragma once

#include <vector>

#include "DatabaseManager.h"

//#include "Hero.h"

class Database {
public:
	Database();

	std::vector<string> Heroes;

	//Hero getAHero(int id);

	void listHeroes();
private:
	void loadHeroesFromDatabase();

	
};