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

				this->currentAttackerPointer++;
				
				this->setNextState();

				break;
			case SPELL_SELECTION:
				this->selectSpellScreen();

				break;
			case SPELL_CASTING:
				this->castSpellScreen();

				this->manageSupportBuffs();

				this->currentAttackerPointer++;

				this->setNextState();

				break;
			case ENEMY_TURN:
				this->enemyTurnScreen();

				this->manageSupportBuffs();

				this->currentAttackerPointer++;

				this->setNextState();

				break;
			case DEFFENDING:
				this->deffendingScreen();

				this->manageSupportBuffs();

				this->setNextState();
				break;
			case ESCAPING:
				this->escapingScreen();

				this->manageSupportBuffs();

				this->setNextState();
				break;
			case DEFEAT:
				return;

				break;
			case VICTORY:
				return;

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

	for (Enemy& enemy : enemyParty) {
		if (!enemy.isDead()) {
			aliveEnemy = true;

			break;
		}
	}

	if (!aliveEnemy) {
		this->battleState = VICTORY;

		return;
	}

	// Check the next attacker to set SELECT_ACTION or ENEMY_ATTACKING
	this->attackOrder.clear();

	for (int i = 0; i < this->party.size(); i++) {
		Hero* hero = this->party[i];

		attackOrder.emplace_back(i, hero->SpeedTotal, HERO, hero->isDead());
	}

	for (int i = 0; i < this->enemyParty.size(); i++) {
		Enemy* enemy = &(this->enemyParty[i]);

		attackOrder.emplace_back(i, enemy->SpeedTotal, ENEMY, enemy->isDead());
	}

	std::size_t actorSpeedSizes = attackOrder.size();

	int i, j;

	bool swaped = false;

	for (i = 0; i < actorSpeedSizes - 1; i++) {
		swaped = false;

		for (j = 0; j < actorSpeedSizes - i - 1; j++) {
			if (attackOrder[j].Speed < attackOrder[j + 1].Speed) {
				std::swap(attackOrder[j], attackOrder[j + 1]);

				swaped = true;
			}
		}

		if (!swaped) {
			break;
		}
	}

	this->currentAttackerPointer = this->currentAttackerPointer >= this->roundSize ? 0 : currentAttackerPointer;

	this->currentAttacker = &(this->attackOrder[currentAttackerPointer]);

	while (this->currentAttacker->IsDead) {
		this->currentAttackerPointer++;

		this->currentAttacker = &(this->attackOrder[currentAttackerPointer]);
	}

	this->battleState = this->currentAttacker->TypeOfActor == HERO ? SELECT_ACTION : ENEMY_TURN;
}

void Battle::startingScreen()
{
	std::string battleStartHeader = "";

	std::string auxHeroName, auxEnemyName, auxVersus;

	int enemyPartySize = (int)enemyParty.size(), partySize = (int)party.size();

	int biggestParty = enemyPartySize >= partySize ? enemyPartySize : partySize;

	battleStartHeader += "\n\n\n\n\n\n";
	battleStartHeader += "\t+-------------------------------------------+\n";
	battleStartHeader += "\t|                Battle Start!              |\n";
	battleStartHeader += "\t+-------------------------------------------+\n";

	for (int i = 0; i < biggestParty; i++) {
		auxVersus = i > 0 ? "\t\t\t\t" : "\t\t VS \t";

		auxEnemyName = i < enemyPartySize ? "\t\t" + enemyParty[i].Name : "\t\t";

		auxHeroName = i < partySize ? party[i]->Name : "";

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
			this->battleState = ENEMY_SELECTION;

			validChoice = true;

			break;
		case 2:
			this->battleState = SPELL_SELECTION;

			validChoice = true;

			break;
		case 3:
			this->battleState = DEFFENDING;

			validChoice = true;

			break;
		case 4:
			this->battleState = ESCAPING;

			validChoice = true;

			break;
		default: 
			std::cout << "Invalid input!";

			std::this_thread::sleep_for(std::chrono::seconds(1));

			break;
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

		this->currentEnemy = &(enemyParty[inputEnemySelected]);

		std::string enemyName = currentEnemy->Name;

		if (currentEnemy->HpCurrent <= 0) {
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
	this->printBattle();

	this->calculatePhysicalDamage(currentHero, currentEnemy);
}

void Battle::manageSupportBuffs() 
{
	std::vector<int> positionsToRemove;

	for (int i = 0; i < this->activeSupportBuffs.size(); i++) {
		activeSupportBuff activeBuff = this->activeSupportBuffs[i];

		activeBuff.ReamaningRounds--;

		if (activeBuff.expired()) {
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
	this->printBattle();

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

		FancyDialog(this->currentHero->Name + " casted " + supportSpell->Name + "!\n", 15);

		// If the support buff is already active, just renew the rounds
		for (activeSupportBuff supportBuff : activeSupportBuffs) {
			if (supportSpell->SupportBuff == supportBuff.SupportBuff) {
				supportBuff.ReamaningRounds += supportSpell->Rounds + 1;

				break;
			}
		}

		// If not, add it to the acrtiveSupportBuffs vector
		activeSupportBuffs.emplace_back(supportSpell->SupportBuff, supportSpell->Rounds + 1);

		break;
	}
	}
}

void Battle::deffendingScreen() 
{
	this->printBattle();

	// TODO deffend logic
	std::cout << "Deffeding does nothing right now!";

	std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Battle::escapingScreen()
{
	this->printBattle();

	// TODO escape logic
	std::cout << "You can't escape right now!";

	std::this_thread::sleep_for(std::chrono::seconds(1));
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
		Enemy* currentEnemy = &(enemyParty[i]);

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

void Battle::enemyTurnScreen() 
{
	this->printBattle();

	std::string enemyName = this->currentEnemy->Name;

	std::cout << enemyName << " turn!\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(333));

	std::srand((unsigned)time(0));

	int targetSelector = rand() % party.size();

	Hero* heroTarget = party[targetSelector];

	// Checking if the enemy isn't trying to attack a dead hero
	while (true) {
		if (!heroTarget->isDead()) {
			break;
		}

		targetSelector = rand() % party.size();

		heroTarget = party[targetSelector];
	}

	this->calculatePhysicalDamage(currentEnemy, heroTarget);
}

Battle::Battle(Game* game, std::vector<int> enemyPartyIds)
{
	this->party = game->GameParty->PartyMembers;

	this->database = game->GameDatabase;

	for (int enemyId : enemyPartyIds) {
		this->enemyParty.push_back(game->GameDatabase->CreateAEnemy(enemyId));
	}

	this->currentRound = 1;
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


