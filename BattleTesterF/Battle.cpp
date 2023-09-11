#include "Battle.h"

void Battle::battleStart()
{
	system("cls");

	string battleStartHeader = "";

	string auxHeroName;

	battleStartHeader += "\n\n\n\n\n\n";
	battleStartHeader += "\t+-----------------------------------+\n";
	battleStartHeader += "\t|          Battle Start!            |\n";
	battleStartHeader += "\t+-----------------------------------+\n";

	for (int i = 0; i < enemyParty.size(); i++) {
		battleStartHeader += "\t\t" + enemyParty[i].Name;

		if (i == 0) {
			auxHeroName = party->PartyMembers[i].Name;

			battleStartHeader += "\t VS \t" + party->PartyMembers[i].Name + "\n\n";
		}
		else {
			auxHeroName = i < party->PartyMembers.size() ? "\t    \t" + party->PartyMembers[i].Name : "";

			battleStartHeader += auxHeroName + "\n\n";
		}
	}

	cout << battleStartHeader;

	this_thread::sleep_for(chrono::seconds(5));

	system("cls");
}

Battle::Battle(Game* game, vector<int> enemyPartyIds)
{
	party = game->GameParty;

	for (int i = 0; i < enemyPartyIds.size(); i++) {
		enemyParty.push_back(game->GameDatabase->getAEnemy(enemyPartyIds[i]));
	}

}
