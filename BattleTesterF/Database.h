#pragma once

#include <vector>

#include "DatabaseManager.h"

#include "Hero.h"
#include "Enemy.h"
#include "SupportSpell.h"
#include "DamageSpell.h"
#include "BuffSpell.h"

class Database {
public:
	Database();

	std::vector<Hero> Heroes;

	std::vector<Enemy> Enemies;

	std::vector<SupportSpell> SupportSpells;

	std::vector<DamageSpell> DamageSpells;

	std::vector<BuffSpell> BuffSpells;

	Hero* getAHero(int id);

	Enemy* getAEnemy(int id);

	Enemy CreateAEnemy(int id);

	SupportSpell* getASupportSpell(SpellInterface* spell);

	DamageSpell* getADamageSpell(SpellInterface* spell);

	BuffSpell* getABuffSpell(SpellInterface* spell);

	SpellInterface* getASpell(int id);

	void listHeroes();

	void listEnemies();
private:
	void loadSpellsFromDatabase();

	void loadHeroesFromDatabase();

	void loadEnemiesFromDatabase();

};