#include "Party.h"

Party::Party(vector<int> idHeroes, Database* gameDatabase)
{
	this->database = gameDatabase;

	for (int i = 0; i < idHeroes.size(); i++) {
		this->partyMembers.push_back(database->getAHero(idHeroes[i]));
	}
}

void Party::addToParty(int heroId)
{
	Hero findHero = database->getAHero(heroId);

	partyMembers.push_back(findHero);
}
