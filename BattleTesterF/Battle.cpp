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

	this_thread::sleep_for(chrono::seconds(1));

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

	vector<tempSpeedActor> actorSpeedOrder = sortAttackOrder();

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

vector<Battle::tempSpeedActor> Battle::sortAttackOrder()
{
	vector<tempSpeedActor> actorSpeedOrder;

	for (int i = 0; i < party->PartyMembers.size(); i++) {
		Hero currentHero = party->PartyMembers[i];

		actorSpeedOrder.emplace_back(i, currentHero.SpeedTotal, typeOfActorEnum::hero);
	}

	for (int i = 0; i < enemyParty.size(); i++) {
		Enemy currentEnemy = enemyParty[i];

		actorSpeedOrder.emplace_back(i, currentEnemy.SpeedTotal, typeOfActorEnum::enemy);
	}

	int actorSpeedSizes = actorSpeedOrder.size(), i, j;

	bool swaped = false;

	for (i = 0; i < actorSpeedSizes - 1; i++) {
		swaped = false;

		for (j = 0;  j < actorSpeedSizes - i - 1; j++) {
			if (actorSpeedOrder[j].Speed < actorSpeedOrder[j + 1].Speed) {
				swap(actorSpeedOrder[j], actorSpeedOrder[j + 1]);

				swaped = true;
			}
		}

		if (!swaped) {
			break;
		}
	}

	cout << "speed debug" << endl;

	for (i = 0; i < actorSpeedSizes; i++) {
		cout << "Position: " << actorSpeedOrder[i].Position << ", speed: " << actorSpeedOrder[i].Speed << ", type: " << ((actorSpeedOrder[i].TypeOfActor == typeOfActorEnum::hero) ? "hero" : "enemy") << endl;
	}

	return actorSpeedOrder;
}

Battle::tempSpeedActor::tempSpeedActor(int position, int speed, typeOfActorEnum typeOfActor)
{
	this->Position = position;
	this->Speed = speed;
	this->TypeOfActor = typeOfActor;
}
