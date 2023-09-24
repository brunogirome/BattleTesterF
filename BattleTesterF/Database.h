#pragma once

#include <vector>

#include "DatabaseManager.h"

#include "Hero.h"
#include "Enemy.h"
#include "SupportSpell.h"

class Database {
public:
	Database();

	std::vector<Hero> Heroes;

	std::vector<Enemy> Enemies;

	std::vector<SupportSpell> SupportSpells;

	Hero* getAHero(int id);

	Enemy* getAEnemy(int id);

	SupportSpell* getASupportSpell(int id);

	SpellInterface* getASpell(int id);

	void listHeroes();

	void listEnemies();
private:
	void loadSpellsFromDatabase();

	void loadHeroesFromDatabase();

	void loadEnemiesFromDatabase();

};