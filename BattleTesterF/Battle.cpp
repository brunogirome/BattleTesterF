#include "Battle.h"

void Battle::start()
{
	bool ended = false;

	this->battleState = STARTING;

	this->roundSize = this->party.size() + this->enemyParty.size();

	this->currentAttackerPointer = 0;

	while (!ended) {
		system("cls");

		switch (this->battleState) {
		case STARTING:
			this->startingScreen();

			this->setNextState();
			break;
		case SELECT_ACTION:
			this->currentHero = this->party[this->currentAttacker->Position];

			this->selectActionScreen();

			break;
		case ENEMY_SELECTION:
			this->selectEnemyScreen();

			break;
		case HERO_ATTACKING:
			this->heroAttackingScreen();
			
			this->manageSupportBuffs();
			
			this->setNextState();

			break;
		case SPELL_SELECTION:
			this->selectSpellScreen();

			break;
		case SPELL_CASTING:
			this->castSpellScreen();

			this->manageSupportBuffs();

			this->setNextState();
			break;
		}
	}
}

void Battle::setNextState()
{
	bool aliveHero = false;

	// Check if DEFEAT
	for (Hero* hero : this->party) {
		if (!hero->isDead()) {
			aliveHero = true;

			break;
		}
	}

	if (!aliveHero) {
		this->battleState = DEFEAT;

		return;
	}

	// Check if VICTORY
	bool aliveEnemy = false;

	for (Enemy* enemy : enemyParty) {
		if (!enemy->isDead()) {
			aliveEnemy = true;

			break;
		}
	}

	if (!aliveEnemy) {
		this->battleState = VICTORY;

		return;
	}

	// Check the next attacker to set SELECT_ACTION or ENEMY_ATTACKING
	this->setNextAttacker();

	this->battleState = this->currentAttacker->TypeOfActor == HERO ? SELECT_ACTION : ENEMY_ATTACKING;
}

void Battle::startingScreen()
{
	std::string battleStartHeader = "";

	std::string auxHeroName, auxEnemyName, auxVersus;

	int enemyPartySize = (int)enemyParty.size(), partySize = (int)party->PartyMembers.size();

	int biggestParty = enemyPartySize >= partySize ? enemyPartySize : partySize;

	battleStartHeader += "\n\n\n\n\n\n";
	battleStartHeader += "\t+-------------------------------------------+\n";
	battleStartHeader += "\t|                Battle Start!              |\n";
	battleStartHeader += "\t+-------------------------------------------+\n";

	for (int i = 0; i < biggestParty; i++) {
		auxVersus = i > 0 ? "\t\t\t\t" : "\t\t VS \t";

		auxEnemyName = i < enemyPartySize ? "\t\t" + enemyParty[i]->Name : "\t\t";

		auxHeroName = i < partySize ? party->PartyMembers[i]->Name : "";

		battleStartHeader += auxEnemyName + auxVersus + auxHeroName + "\n\n";
	}

	std::cout << battleStartHeader;

	std::this_thread::sleep_for(std::chrono::seconds(1));	
}

void Battle::selectActionScreen() 
{
	bool validChoice = false, firstExecutuion = true;

	int selectedAction;

	std::string heroName = currentHero->Name;

	while (!validChoice) {
		if (!firstExecutuion) {
			system("cls");
		}

		this->printBattle();

		FancyDialog(heroName + " turn!\n\nSelect your action:\n", 5);

		std::cout << "[1] Attack | [2] Spells | [3] Deffend | [4] Escape\n";

		std::cin >> selectedAction;

		switch (selectedAction) 
		{
		case 1: 
		{
			this->battleState = HERO_ATTACKING;

			validChoice = true;
		}
		case 2:
		{
			this->battleState = SPELL_SELECTION;

			validChoice = true;

			break;
		}
		case 3:
		{
			// TODO deffend logic
			std::cout << "Deffeding does nothing right now!";

			std::this_thread::sleep_for(std::chrono::seconds(1));

			validChoice = true;

			break;
		}
		case 4:
		{
			// TODO escape logic
			std::cout << "You can't escape right now!";

			std::this_thread::sleep_for(std::chrono::seconds(1));

			validChoice = true;

			break;
		}
		default: 
		{
			std::cout << "Invalid input!";

			std::this_thread::sleep_for(std::chrono::seconds(1));

			break;
		}
		}
		
		firstExecutuion = false;
	}
}

void Battle::selectEnemyScreen()
{
	int inputEnemySelected;

	bool validEnemyOption = false;

	while (!validEnemyOption) {
		system("cls");

		this->printBattle();

		FancyDialog("Select one enemy (0 cancel): ", 2);

		std::cin >> inputEnemySelected;

		if (inputEnemySelected == 0) {
			this->battleState = SELECT_ACTION;

			validEnemyOption = true;

			return;
		}

		inputEnemySelected -= 1;

		if (inputEnemySelected >= enemyParty.size() || inputEnemySelected < 0) {
			std::cout << "Invalid input!";

			std::this_thread::sleep_for(std::chrono::seconds(1));

			continue;
		}

		this->selectedEnemy = enemyParty[inputEnemySelected];

		std::string enemyName = selectedEnemy->Name;

		if (selectedEnemy->HpCurrent <= 0) {
			std::cout << enemyName << " is dead, select another enemy!";

			std::this_thread::sleep_for(std::chrono::seconds(1));

			continue;
		}

		validEnemyOption = true;
	}

	this->battleState = HERO_ATTACKING;
}

void Battle::heroAttackingScreen()
{
	this->calculatePhysicalDamage(currentHero, selectedEnemy);
}

void Battle::setNextAttacker()
{
	std::vector<actorAttackOrder> actorsSpeedOrder;

	for (int i = 0; i < this->party.size(); i++) {
		Hero* currentHero = this->party[i];

		actorsSpeedOrder.emplace_back(i, currentHero->SpeedTotal, HERO, currentHero->isDead());
	}

	for (int i = 0; i < this->enemyParty.size(); i++) {
		Enemy* currentEnemy = this->enemyParty[i];

		actorsSpeedOrder.emplace_back(i, currentEnemy->SpeedTotal, ENEMY, currentEnemy->isDead());
	}

	std::size_t actorSpeedSizes = actorsSpeedOrder.size();

	int i, j;

	bool swaped = false;

	for (i = 0; i < actorSpeedSizes - 1; i++) {
		swaped = false;

		for (j = 0; j < actorSpeedSizes - i - 1; j++) {
			if (actorsSpeedOrder[j].Speed < actorsSpeedOrder[j + 1].Speed) {
				std::swap(actorsSpeedOrder[j], actorsSpeedOrder[j + 1]);

				swaped = true;
			}
		}

		if (!swaped) {
			break;
		}
	}

	this->attackOrder = actorsSpeedOrder;

	this->currentAttackerPointer = this->currentAttackerPointer >= this->roundSize ? 0 : currentAttackerPointer;

	this->currentAttacker = &(this->attackOrder[currentAttackerPointer]);

	while (this->currentAttacker->IsDead) {
		this->currentAttackerPointer++;

		this->currentAttacker = &(this->attackOrder[currentAttackerPointer]);
	}
}

void Battle::manageSupportBuffs() 
{
	std::vector<int> positionsToRemove;

	for (int i = 0; i < this->activeSupportBuffs.size(); i++) {
		activeSupportBuff* activeBuff = this->activeSupportBuffs[i];

		activeBuff->ReamaningRounds--;

		if (activeBuff->expired()) {
			positionsToRemove.push_back(i);
		}
	}

	if (positionsToRemove.size() == 0) {
		return;
	}

	for (int position : positionsToRemove) {
		this->activeSupportBuffs.erase(activeSupportBuffs.begin() - 1 + position);
	}
}

void Battle::calculatePhysicalDamage(CombatActorInterface* attackerActor, CombatActorInterface* deffenderActor) {
	int damage = attackerActor->MeelePowerTotal - deffenderActor->MeeleDefenseTotal;

	damage = damage < 0 ? 1 : damage;

	std::string deffenderName = deffenderActor->Name;

	FancyDialog("Attacking " + deffenderName + "...", 10);

	std::this_thread::sleep_for(std::chrono::milliseconds(333));

	FancyDialog("Dealt " + std::to_string(damage) + " damage on " + deffenderName + "!", 15);

	std::this_thread::sleep_for(std::chrono::milliseconds(1200));

	deffenderActor->HpCurrent -= damage;

	if (deffenderActor->isDead()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(333));

		FancyDialog(attackerActor->Name + " killed " + deffenderName + "!", 15);

		std::this_thread::sleep_for(std::chrono::milliseconds(999));
	}
}

void Battle::selectSpellScreen()
{
	std::vector<int> heroSpells = this->currentHero->Spells;

	bool validSpellOption = false;

	int inputSpellSelect;

	while (!validSpellOption) {
		system("cls");

		this->printBattle();

		FancyDialog("Select a spell to cast (0 return):", 2);

		std::cin >> inputSpellSelect;

		for (int i = 0; i < heroSpells.size(); i++) {
			SpellInterface* spell = this->database->getASpell(heroSpells[i]);

			std::cout << "[" << i + 1 << "] " << spell->Name << " | " << spell->Description << '\n';
		}

		if (inputSpellSelect == 0) {
			validSpellOption = true;

			this->battleState = SELECT_ACTION;

			return;
		}

		inputSpellSelect -= 1;

		if (inputSpellSelect >= enemyParty.size() || inputSpellSelect < 0) {
			std::cout << "Invalid input!";

			std::this_thread::sleep_for(std::chrono::seconds(1));

			continue;
		}

		this->selectedSpell = this->database->getASpell(heroSpells[inputSpellSelect]);

		validSpellOption = true;
	}

	this->battleState = SPELL_CASTING;
}

void Battle::castSpellScreen() 
{
	switch (selectedSpell->SpellType) {
	case BUFF:
	{

	}
	case DAMAGE:
	{

	}
	case SUPPORT:
	{
		SupportSpell* supportSpell = this->database->getASupportSpell(selectedSpell);

		FancyDialog(currentHero->Name + " casted " + supportSpell->Name + "!\n", 15);

		// If the support buff is already active, just renew the rounds
		for (activeSupportBuff* supportBuff : activeSupportBuffs) {
			if (supportSpell->SupportBuff == supportBuff->SupportBuff) {
				supportBuff->ReamaningRounds += supportSpell->Rounds + 1;

				break;
			}
		}

		// If not, add it to the acrtiveSupportBuffs vector
		activeSupportBuffs.emplace_back(supportSpell->SupportBuff, supportSpell->Rounds + 1);

		break;
	}
	}
}

void Battle::printBattle()
{
	std::string uiLines = "";

	std::string auxNameEnemy, auxHeroName;

	int enemyPartySize = (int)enemyParty.size(), partySize = (int)party.size();

	drawLine(59);

	std::cout << "Enemy line: " << '\n';

	drawLine(59);

	for (int i = 0; i < enemyPartySize; i++) {
		Enemy* currentEnemy = enemyParty[i];

		std::cout << "[" << i + 1 << "] " << currentEnemy->Name;

		if (!currentEnemy->isDead()) {
			std::cout << " HP: ??/??" << '\n';
		}
		else {
			std::cout << " DEAD" << '\n';
		}
	}

	std::cout << '\n' << "Your team:" << '\n';

	drawLine(59);

	for (int i = 0; i < partySize; i++) {
		Hero* partyMember = party[i];

		std::cout << '\n' << partyMember->Name << '\n';

		if (!partyMember->isDead()) {
			std::cout << "HP: " << partyMember->HpCurrent << "/" << partyMember->HpTotal << '\n';

			std::cout << "Mana: " << partyMember->ManaCurrent << "/" << partyMember->ManaTotal << '\n';
		}
		else {
			std::cout << " DEAD\n\n";
		}
	}

	drawLine(59);

	std::cout << uiLines;
}

Battle::Battle(Game* game, std::vector<int> enemyPartyIds)
{
	this->party = game->GameParty->PartyMembers;

	this->database = game->GameDatabase;

	for (int enemyId : enemyPartyIds) {
		this->enemyParty.push_back(game->GameDatabase->getAEnemy(enemyId));
	}

	this->currentRound = 1;
}

// ----------------------------------

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

					if (attackerPointer >= roudSize) {
						attackerPointer = 0;

						i = 0;

						deadEnemies = 0;

						deadHeroes = 0;

						continue;
					}
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
	Enemy* currentEnemy = enemyParty[attackerPosition];

	std::string enemyName = currentEnemy->Name;

	std::cout << enemyName << " turn!\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(333));

	std::srand((unsigned) time(0));

	bool invalidTarget = true;

	int targetSelector = rand() % party->PartyMembers.size();

	Hero* heroTarget = party->PartyMembers[targetSelector];

	// Checking if the enemy isn't trying to attack a dead hero
	while (invalidTarget) {
		if (!heroTarget->isDead()) {
			invalidTarget = false;

			continue;
		}

		targetSelector = rand() % party->PartyMembers.size();

		heroTarget = party->PartyMembers[targetSelector];
	}

	int damage = currentEnemy->MeelePowerTotal * 5 - (int)(heroTarget->MeeleDefenseTotal);

	damage = damage < 0 ? 1 : damage;

	std::string targetHeroName = heroTarget->Name;

	FancyDialog(enemyName + " is attacking " + targetHeroName + "!", 15);

	std::this_thread::sleep_for(std::chrono::milliseconds(999));

	FancyDialog("Dealt " + std::to_string(damage) + " damage on " + targetHeroName + "!", 15);

	std::this_thread::sleep_for(std::chrono::milliseconds(1200));

	heroTarget->HpCurrent -= damage;

	if (heroTarget->isDead()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(333));

		FancyDialog(enemyName + " killed " + targetHeroName + "!", 15);

		std::this_thread::sleep_for(std::chrono::milliseconds(888));
	}
	sortAttackOrder();

	system("cls");
}

void Battle::selectAction(int attackerPosition)
{
	int battleOption = 0;

	bool optionInvalid = true, firstExecution = true;

	Hero* currentHero = party[attackerPosition];

	std::string heroName = currentHero->Name;

	// Battle option select
	while (optionInvalid) {
		std::cout << heroName << " turn!\n\nSelect your action:\n[1] Attack [2] Spells [3] Deffend\n";

		std::cin >> battleOption;

		if (!firstExecution) {
			printBattle();
		}

		optionInvalid = battleOption > 3 || battleOption < 1;

		if (optionInvalid) {
			std::cout << "Invalid option!" << '\n';

			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		else {

		}

		system("cls");

		firstExecution = false;
	}

	// Executing option
	switch (battleOption) {
	case 1:
	{
		bool enemySelectedInvalid = true;

		std::size_t inputEnemySelected;

		while (enemySelectedInvalid) {

		}
	}
		
	}

	// Spell variables
	int selectedSpellPosition = 0;

	std::vector<int> heroSpells = currentHero->Spells;

	while (optionInvalid) {
		std::cout << heroName << " turn!\n\nSelect your action:\n[1] Attack [2] Spells [3] Deffend\n";

		std::cin >> battleOption;

		if (!firstExecution) {
			printBattle();
		}

		switch (battleOption) {
		case 1:
			optionInvalid = false;

			break;
		case 2:
		{
			bool invalidSpellOption = true;

			while (invalidSpellOption) {
				std::cout << "Select a spell:\n";

				std::cout << "([0] to go back)\n\n";

				for (int i = 0; i < heroSpells.size(); i++) {
					SpellInterface* displaySpell = database->getASpell(heroSpells[i]);

					std::cout << "[" << (i + 1) << "] " << displaySpell->Name << ": " << displaySpell->Description << '\n';
				}

				std::cin >> selectedSpellPosition;

				if (selectedSpellPosition == 0) {
					optionInvalid = false;

					invalidSpellOption = false;

					continue;
				}
				else if (selectedSpellPosition > heroSpells.size()) {
					std::cout << "Invalid input!\n";

					std::this_thread::sleep_for(std::chrono::seconds(1));

					continue;
				}

				invalidSpellOption = false;
			}

			break;
		}
		case 3: 
		{

		}
		default:

		}

		firstExecution = false;
	}

	switch (battleOption) {
	case 1:
		system("cls");

		

		

		while (enemySelectedInvalid && battleOption == 1) {
			printBattle();

			std::cout << "Select one enemy: ";

			std::cin >> inputEnemySelected;

			inputEnemySelected -= 1;

			if (inputEnemySelected >= enemyParty.size() || inputEnemySelected < 0) {
				std::cout << "Invalid input!";

				std::this_thread::sleep_for(std::chrono::seconds(1));

				system("cls");

				continue;
			}

			Enemy* selectedEnemy = enemyParty[inputEnemySelected];

			std::string enemyName = selectedEnemy->Name;

			if (selectedEnemy->HpCurrent <= 0) {
				std::cout << enemyName << " is dead, select another enemy!";

				std::this_thread::sleep_for(std::chrono::seconds(1));

				system("cls");

				continue;
			}

			int damage = currentHero->MeelePowerTotal - selectedEnemy->MeeleDefenseTotal;

			damage = damage < 0 ? 1 : damage;

			FancyDialog("Attacking " + enemyName + "...", 10);

			std::this_thread::sleep_for(std::chrono::milliseconds(333));

			FancyDialog("Dealt " + std::to_string(damage) + " damage on " + enemyName + "!", 15);

			std::this_thread::sleep_for(std::chrono::milliseconds(1200));

			selectedEnemy->HpCurrent -= damage;

			if (selectedEnemy->isDead()) {
				std::this_thread::sleep_for(std::chrono::milliseconds(333));

				FancyDialog(heroName + " killed " + enemyName + "!", 15);

				std::this_thread::sleep_for(std::chrono::milliseconds(999));
			}

			system("cls");

			enemySelectedInvalid = false;
		}
		break;
	case 2:
		SpellInterface * selectedSpell = database->getASpell(heroSpells[selectedSpellPosition - 1]);

		switch (selectedSpell->SpellType) {
		case SpellTypesEnum::DAMAGE:
			break;
		case SpellTypesEnum::BUFF:
			break;
		case SpellTypesEnum::SUPPORT:
			SupportSpell* supportSpell = database->getASupportSpell(selectedSpell->Id);

			FancyDialog("Casted " + supportSpell->Name + "!\n", 10);

			break;
		}

		optionInvalid = false;

		system("cls");

		break;
	}

	sortAttackOrder();
}

Battle::actorAttackOrder::actorAttackOrder(int position, int speed, typeOfActorEnum typeOfActor, bool isDead)
{
	this->Position = position;
	this->Speed = speed;
	this->TypeOfActor = typeOfActor;
	this->IsDead = isDead;
}

Battle::activeSupportBuff::activeSupportBuff(SupportBuffsEnum supportBuff, int reamaningRounds)
{
	this->SupportBuff = supportBuff;
	this->ReamaningRounds = reamaningRounds;
}

bool Battle::activeSupportBuff::expired()
{
	return this->ReamaningRounds < 1;
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


