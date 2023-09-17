#pragma once

#include "Database.h"

class EnemyParty
{
private:
	Database* database;

public:
	std::vector<Enemy> Enemies;

	EnemyParty(std::vector<int> enemiesId, Database* gameDatabase);
};

