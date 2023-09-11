#include "Battle.h"

void Battle::battleStart()
{
	system("cls");

	string battleStartHeader = "";

	string auxHeroName, auxEnemyName, auxVersus;

	int enemyPartySize = (int)enemyParty.size(), partySize = (int)party->PartyMembers.size();

	int biggestParty = enemyPartySize >= partySize ? enemyPartySize : partySize;

	battleStartHeader += "\n\n\n\n\n\n";
	battleStartHeader += "\t+-----------------------------------+\n";
	battleStartHeader += "\t|          Battle Start!            |\n";
	battleStartHeader += "\t+-----------------------------------+\n";

	for (int i = 0; i < biggestParty; i++) {
		auxVersus = i > 0 ? "\t   \t" : "\t VS \t";

		auxEnemyName = i < enemyPartySize ? "\t\t" + enemyParty[i].Name : "\t\t";

		auxHeroName = i < partySize ? party->PartyMembers[i].Name : "";

		battleStartHeader += auxEnemyName + auxVersus +  auxHeroName + "\n\n";
	}

	cout << battleStartHeader;

	this_thread::sleep_for(chrono::seconds(3));

	system("cls");

	battleInterface();
}

void Battle::battleInterface()
{
	string uiLines = "";

	string auxNameEnemy, auxHeroName;

	int enemyPartySize = (int)enemyParty.size(), partySize = (int)party->PartyMembers.size();

	cout << "Combat started!" << endl;

	drawLine(59);

	cout << "Enemy line: " << endl;

	drawLine(59);
	
	for (int i = 0; i < enemyPartySize; i++) {
		cout << endl << enemyParty[i].Name << endl;

		cout << "HP: ??/??" << endl;
	}

	cout << endl << "Your team:" << endl;

	drawLine(59);

	for (int i = 0; i < partySize; i++) {
		cout << endl << party->PartyMembers[i].Name << endl;

		cout << "HP: " << party->PartyMembers[i].HpCurrent << "/" << party->PartyMembers[i].HpTotal << endl;

		cout << "Mana: " << party->PartyMembers[i].ManaCurrent << "/" << party->PartyMembers[i].ManaTotal << endl;
	}

	drawLine(59);

	cout << uiLines;

	system("pause");
}

Battle::Battle(Game* game, vector<int> enemyPartyIds)
{
	party = game->GameParty;

	for (int i = 0; i < enemyPartyIds.size(); i++) {
		enemyParty.push_back(game->GameDatabase->getAEnemy(enemyPartyIds[i]));
	}

}

string Battle::getLine(int size, string character) {
	string line = "";

	for (int i = 0; i < size; i++) {
		line += character;
	}

	return line;
}

void Battle::drawLine(int size, bool border) {
	string line = border ? "+" : "";

	for (int i = 0; i < size; i++) {
		line += "-";
	}

	line += border ? "+" : "";

	line += "\n";

	cout << line;
}
