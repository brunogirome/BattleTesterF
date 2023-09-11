#pragma once

#include "Database.h"

class EnemyParty
{
private:
	Database* database;

public:
	vector<Enemy> Enemies;

	EnemyParty(vector<int> enemiesId, Database* gameDatabase);
};

