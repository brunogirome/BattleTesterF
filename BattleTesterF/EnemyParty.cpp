#include "EnemyParty.h"

EnemyParty::EnemyParty(std::vector<int> enemiesId, Database* gameDatabase)
{
	this->database = gameDatabase;

	for (int i = 0; i < enemiesId.size(); i++) {
		this->Enemies.push_back(database->getAEnemy(enemiesId[i]));
	}
}
