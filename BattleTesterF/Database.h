#pragma once

#include <vector>

#include "DatabaseManager.h"

#include "Hero.h"
#include "Enemy.h"

class Database {
public:
	Database();

	vector<Hero> Heroes;

	vector<Enemy> Enemies;

	Hero getAHero(int id);

	Enemy getAEnemy(int id);

	void listHeroes();

	void listEnemies();
private:
	void loadHeroesFromDatabase();

	void loadEnemiesFromDatabase();

};