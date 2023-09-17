#include "Battle.h"

void Battle::start()
{
	system("cls");

	std::string battleStartHeader = "";

	std::string auxHeroName, auxEnemyName, auxVersus;

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

	std::cout << battleStartHeader;

	std::this_thread::sleep_for(std::chrono::seconds(1));

	system("cls");

	std::cout << "Combat started!" << '\n';

	std::string finalMessage;

	if (loop()) {
		finalMessage = "You win";
	}
	else {
		finalMessage = "You loose!";
	}

	std::this_thread::sleep_for(std::chrono::seconds(1));

	system("cls");

	std::cout << '\n' << '\n' << "\t\t" << finalMessage;

	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Battle::printBattle()
{
	std::string uiLines = "";

	std::string auxNameEnemy, auxHeroName;

	int enemyPartySize = (int)enemyParty.size(), partySize = (int)party->PartyMembers.size();

	drawLine(59);

	std::cout << "Enemy line: " << '\n';

	drawLine(59);
	
	for (int i = 0; i < enemyPartySize; i++) {
		Enemy* currentEnemy = &(enemyParty[i]);

		std::cout << "[" << i + 1 << "] " << currentEnemy->Name << '\n';

		if (!currentEnemy->isDead()) {
			std::cout << "HP: ??/??" << '\n';
		}
		else {
			std::cout << "DEAD" << '\n';
		}

		delete currentEnemy;
	}

	std::cout << '\n' << "Your team:" << '\n';

	drawLine(59);

	for (int i = 0; i < partySize; i++) {
		Hero* partyMember = &(party->PartyMembers[i]);

		std::cout << '\n' << partyMember->Name << '\n';

		std::cout << "HP: " << partyMember->HpCurrent << "/" << partyMember->HpTotal << '\n';

		std::cout << "Mana: " << partyMember->ManaCurrent << "/" << partyMember->ManaTotal << '\n';

		delete partyMember;
	}

	drawLine(59);

	std::cout << uiLines;
}

Battle::Battle(Game* game, std::vector<int> enemyPartyIds)
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

		std::cout << "Round " << currentRound << '\n';

		printBattle();

		if (currentAttacker.TypeOfActor == typeOfActorEnum::hero) {
			selectAction(currentAttacker.Position);
		}
		else {
			enemyTurn(currentAttacker.Position);
		}

		currentRound++;

		attackerPointer++;
	}
}

void Battle::enemyTurn(int attackerPosition) {
	std::cout << enemyParty[attackerPosition].Name << " turn! " << '\n';

	std::this_thread::sleep_for(std::chrono::milliseconds(333));

	std::srand((unsigned) time(0));

	Enemy* currentEnemy = &(enemyParty[attackerPosition]);

	bool invalidTarget = true;

	int targetSelector = rand() % party->PartyMembers.size();

	Hero* heroTarget = &(party->PartyMembers[targetSelector]);

	// Checking if the enemy isn't trying to attack a dead hero
	while (invalidTarget) {
		if (!heroTarget->isDead()) {
			invalidTarget = false;

			continue;
		}

		targetSelector = rand() % party->PartyMembers.size();

		heroTarget = &(party->PartyMembers[targetSelector]);
	}

	int damage = currentEnemy->MeelePowerTotal - (int)(heroTarget->MeeleDefenseTotal);

	damage = damage < 0 ? 1 : damage;
}

void Battle::selectAction(int attackerPosition)
{
	int battleOption, enemySelected;

	bool optionInvalid = true, enemySelectedInvalid = true;

	Hero* currentHero = &(party->PartyMembers[attackerPosition]);

	std::string heroName = currentHero->Name;

	// Battle option select
	while (optionInvalid) {
		std::cout << heroName << " turn!\n\nSelect your action:\n[1] Attack [2] Defend\n";

		std::cin >> battleOption;

		switch (battleOption) {
			case 1:
				optionInvalid = false;

				break;
			case 2: 
				std::cout << "Defend does nothing right now!" << '\n';

				std::this_thread::sleep_for(std::chrono::seconds(1));

				system("cls");

				optionInvalid = false;
				break;
			default:
				std::cout << "Invalid option!" << '\n';

				std::this_thread::sleep_for(std::chrono::seconds(1));

				system("cls");

				break;
		}
	}

	system("cls");

	while (enemySelectedInvalid && battleOption == 1) {
		printBattle();

		std::cout << "Select one enemy: ";

		std::cin >> enemySelected;

		enemySelected -= 1;

		if (enemySelected > enemyParty.size()) {
			std::cout << "Invalid enemy!";

			std::this_thread::sleep_for(std::chrono::seconds(1));

			system("cls");

			continue;
		}

		Enemy* selectedEnemy = &(enemyParty[enemySelected]);

		std::string enemyName = selectedEnemy->Name;

		if (selectedEnemy->HpCurrent <= 0) {
			std::cout << enemyName << "is dead, select another enemy!";

			std::this_thread::sleep_for(std::chrono::seconds(1));

			system("cls");

			continue;
		}

		int damage = currentHero->MeelePowerTotal - (int)(selectedEnemy->MeeleDefenseTotal);

		damage = damage < 0 ? 1 : damage;

		std::cout << "Attacking " << enemyName << "..." << '\n' << '\n';

		std::this_thread::sleep_for(std::chrono::milliseconds(333));

		std::cout << "Dealt " << damage << " damage on " << enemyName << "!" << '\n' << '\n';

		std::this_thread::sleep_for(std::chrono::seconds(1));

		int enemyCurrentHp = enemyParty[enemySelected].HpCurrent - damage;

		enemyParty[enemySelected].HpCurrent = enemyCurrentHp;

		if (enemyCurrentHp <= 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(333));

			std::cout << heroName << " killed " << enemyName << "!" << '\n';

			std::this_thread::sleep_for(std::chrono::milliseconds(666));
		}

		system("cls");

		enemySelectedInvalid = false;
	}

	sortAttackOrder();
}

void Battle::sortAttackOrder()
{
	std::vector<actorAttackOrder> actorsSpeedOrder;

	for (int i = 0; i < party->PartyMembers.size(); i++) {
		Hero* currentHero = &(party->PartyMembers[i]);

		actorsSpeedOrder.emplace_back(i, currentHero->SpeedTotal, typeOfActorEnum::hero, currentHero->isDead());

		delete currentHero;
	}

	for (int i = 0; i < enemyParty.size(); i++) {
		Enemy* currentEnemy = &(enemyParty[i]);

		actorsSpeedOrder.emplace_back(i, currentEnemy->SpeedTotal, typeOfActorEnum::enemy, currentEnemy->isDead());

		delete currentEnemy;
	}

	int actorSpeedSizes = (int)actorsSpeedOrder.size(), i, j;

	bool swaped = false;

	for (i = 0; i < actorSpeedSizes - 1; i++) {
		swaped = false;

		for (j = 0;  j < actorSpeedSizes - i - 1; j++) {
			if (actorsSpeedOrder[j].Speed < actorsSpeedOrder[j + 1].Speed) {
				std::swap(actorsSpeedOrder[j], actorsSpeedOrder[j + 1]);

				swaped = true;
			}
		}

		if (!swaped) {
			break;
		}
	}

	/*std::cout << "speed debug" << '\n';

	for (i = 0; i < actorSpeedSizes; i++) {
		std::cout << "Position: " << actorSpeedOrder[i].Position << ", speed: " << actorSpeedOrder[i].Speed << ", type: " << ((actorSpeedOrder[i].TypeOfActor == typeOfActorEnum::hero) ? "hero" : "enemy") << '\n';
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

std::string Battle::getLine(int size, std::string character) {
	std::string line = "";

	for (int i = 0; i < size; i++) {
		line += character;
	}

	return line;
}

void Battle::drawLine(int size, bool border) {
	std::string line = border ? "+" : "";

	for (int i = 0; i < size; i++) {
		line += "-";
	}

	line += border ? "+" : "";

	line += "\n";

	std::cout << line;
}
