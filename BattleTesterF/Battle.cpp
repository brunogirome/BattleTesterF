#include "Battle.h"

void Battle::start()
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

	cout << "Combat started!" << endl;

	string finalMessage;

	if (loop()) {
		finalMessage = "You win";
	}
	else {
		finalMessage = "You loose!";
	}

	this_thread::sleep_for(chrono::seconds(1));

	system("cls");

	cout << endl << endl << "\t\t" << finalMessage;

	this_thread::sleep_for(chrono::seconds(1));
}

void Battle::printBattle()
{
	string uiLines = "";

	string auxNameEnemy, auxHeroName;

	int enemyPartySize = (int)enemyParty.size(), partySize = (int)party->PartyMembers.size();

	drawLine(59);

	cout << "Enemy line: " << endl;

	drawLine(59);
	
	for (int i = 0; i < enemyPartySize; i++) {
		cout << "[" << i + 1 << "] " << enemyParty[i].Name << endl;

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
}

Battle::Battle(Game* game, vector<int> enemyPartyIds)
{
	party = game->GameParty;

	for (int i = 0; i < enemyPartyIds.size(); i++) {
		enemyParty.push_back(game->GameDatabase->getAEnemy(enemyPartyIds[i]));
	}

	currentRound = 1;
}

bool Battle::loop()
{
	sortAttackOrder();

	const int roudSize = (int)attackOrder.size();

	int attackerPointer = 0, deadEnemies, deadHeroes;

	while (true) {
		deadEnemies = 0;

		deadHeroes = 0;

		attackerPointer = attackerPointer >= roudSize ? 0 : attackerPointer;

		// Checking if player won or lost the battle
		for (int i = 0; i < attackOrder.size(); i++) {
			actorAttackOrder attacker = attackOrder[i];

			if (attacker.IsDead) {
				if (attackerPointer == i) {
					attackerPointer++;
				}

				switch (attacker.TypeOfActor) {
					case typeOfActorEnum::enemy:
						deadEnemies++;

						break;
					case typeOfActorEnum::hero:
						deadHeroes++;

						break;
				}

				if (deadEnemies == enemyParty.size()) {
					return true;
				}

				if (deadHeroes == party->PartyMembers.size()) {
					return false;
				}
			}
		}

		actorAttackOrder currentAttacker = attackOrder[attackerPointer];

		cout << "Round " << currentRound << endl;

		printBattle();

		if (currentAttacker.TypeOfActor == typeOfActorEnum::hero) {
			selectAction(attackerPointer);
		}
		else {
			cout << "Enemy round" << endl;
		}

		currentRound++;

		attackerPointer++;
	}
}

void Battle::selectAction(int attackerPosition)
{
	int battleOption, enemySelected;

	bool optionInvalid = true, enemySelectedInvalid = true;

	Hero currentHero = party->PartyMembers[attackerPosition];

	string heroName = currentHero.Name;

	// Battle option select
	while (optionInvalid) {
		cout << heroName << " turn!\n\nSelect your action: " << endl << "[1] - Attack [2] - Defend" << endl;

		cin >> battleOption;

		switch (battleOption) {
			case 1:
				optionInvalid = false;

				break;
			case 2: 
				cout << "Defend does nothing right now!" << endl;

				this_thread::sleep_for(chrono::seconds(1));

				system("cls");

				optionInvalid = false;
				break;
			default:
				cout << "Invalid option!" << endl;

				this_thread::sleep_for(chrono::seconds(1));

				system("cls");

				break;
		}
	}

	system("cls");

	while (enemySelectedInvalid && battleOption == 1) {
		printBattle();

		cout << "Select one enemy: ";

		cin >> enemySelected;

		enemySelected -= 1;

		if (enemySelected > enemyParty.size()) {
			cout << "Invalid enemy!";

			this_thread::sleep_for(chrono::seconds(1));

			system("cls");

			continue;
		}

		Enemy selectedEnemy = enemyParty[enemySelected];

		if (selectedEnemy.HpCurrent <= 0) {
			cout << "Select another enemy!";

			this_thread::sleep_for(chrono::seconds(1));

			system("cls");

			continue;
		}

		int damage = currentHero.MeelePowerTotal * 10 - (int)(selectedEnemy.MeeleDefenseTotal);

		damage = damage < 0 ? 1 : damage;

		string enemyName = selectedEnemy.Name;

		cout << "Attacking " << enemyName << "..." << endl << endl;

		this_thread::sleep_for(chrono::milliseconds(333));

		cout << "Dealt " << damage << " damage on " << enemyName << "!" << endl << endl;

		this_thread::sleep_for(chrono::seconds(1));

		int enemyCurrentHp = enemyParty[enemySelected].HpCurrent - damage;

		enemyParty[enemySelected].HpCurrent = enemyCurrentHp;

		if (enemyCurrentHp <= 0) {
			this_thread::sleep_for(chrono::milliseconds(333));

			cout << heroName << " killed " << enemyName << "!" << endl;

			this_thread::sleep_for(chrono::milliseconds(666));
		}

		system("cls");

		enemySelectedInvalid = false;
	}

	sortAttackOrder();
}

void Battle::sortAttackOrder()
{
	vector<actorAttackOrder> actorsSpeedOrder;

	bool isDead;

	for (int i = 0; i < party->PartyMembers.size(); i++) {
		Hero currentHero = party->PartyMembers[i];

		isDead = currentHero.HpCurrent <= 0;

		actorsSpeedOrder.emplace_back(i, currentHero.SpeedTotal, typeOfActorEnum::hero, isDead);
	}

	for (int i = 0; i < enemyParty.size(); i++) {
		Enemy currentEnemy = enemyParty[i];

		isDead = currentEnemy.HpCurrent <= 0;

		actorsSpeedOrder.emplace_back(i, currentEnemy.SpeedTotal, typeOfActorEnum::enemy, isDead);
	}

	int actorSpeedSizes = (int)actorsSpeedOrder.size(), i, j;

	bool swaped = false;

	for (i = 0; i < actorSpeedSizes - 1; i++) {
		swaped = false;

		for (j = 0;  j < actorSpeedSizes - i - 1; j++) {
			if (actorsSpeedOrder[j].Speed < actorsSpeedOrder[j + 1].Speed) {
				swap(actorsSpeedOrder[j], actorsSpeedOrder[j + 1]);

				swaped = true;
			}
		}

		if (!swaped) {
			break;
		}
	}

	/*cout << "speed debug" << endl;

	for (i = 0; i < actorSpeedSizes; i++) {
		cout << "Position: " << actorSpeedOrder[i].Position << ", speed: " << actorSpeedOrder[i].Speed << ", type: " << ((actorSpeedOrder[i].TypeOfActor == typeOfActorEnum::hero) ? "hero" : "enemy") << endl;
	}*/

	attackOrder = actorsSpeedOrder;
}

Battle::actorAttackOrder::actorAttackOrder(int position, int speed, typeOfActorEnum typeOfActor, bool isDead)
{
	this->Position = position;
	this->Speed = speed;
	this->TypeOfActor = typeOfActor;
	this->IsDead = isDead;
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
