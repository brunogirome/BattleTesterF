#include "Party.h"

Party::Party(vector<int> idHeroes, Database* database)
{
	this->database = database;

	for (int i = 0; i < idHeroes.size(); i++) {
		this->PartyMembers.push_back(database->getAHero(idHeroes[i]));
	}
}

void Party::addToParty(int heroId)
{
	Hero findHero = database->getAHero(heroId);

	PartyMembers.push_back(findHero);
}
