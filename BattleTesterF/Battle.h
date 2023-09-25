#pragma once

#include "Game.h"

#include "SupportSpell.h"

#include "FancyDialog.h"

enum typeOfActorEnum { HERO, ENEMY };

enum battleStateEnum { STARTING, SELECT_ACTION, ENEMY_SELECTION, HERO_ATTACKING, ENEMY_ATTACKING, SPELL_SELECTION, SPELL_CASTING, VICTORY, DEFEAT };

class Battle
{
private:
	std::vector<Hero*> party;

	Database* database;

	std::vector<Enemy*> enemyParty;

	// Round management
	class actorAttackOrder {
	public:
		int Position;
		int Speed;
		bool IsDead;
		typeOfActorEnum TypeOfActor;

		actorAttackOrder(int position, int speed, typeOfActorEnum typeOfActor, bool isDead);
	};

	class activeSupportBuff {
	public:
		SupportBuffsEnum SupportBuff;
		int ReamaningRounds;

		activeSupportBuff(SupportBuffsEnum supportBuff, int reamaningRounds);

		bool expired();
	};

	std::vector<activeSupportBuff*> activeSupportBuffs;

	std::size_t currentAttackerPointer;

	std::size_t roundSize;

	std::vector<actorAttackOrder> attackOrder;

	actorAttackOrder* currentAttacker;

	void setNextAttacker();

	// Battle State management			
	battleStateEnum battleState;

	void setNextState();

	void startingScreen();

	void selectActionScreen();

	// Utils
	void calculatePhysicalDamage(CombatActorInterface* attackerActor, CombatActorInterface* deffenderActor);

	void castSupportSpell(SupportSpell* spell, Hero* hero);

	// Support spells activation
	// ------------

	int currentRound;

	std::string getLine(int size, std::string character = "-");

	bool loop();

	void drawLine(int size, bool border = false);

	void sortAttackOrder();

	void selectAction(int attackerPosition);

	void enemyTurn(int attackerPosition);

	void printBattle();
public:
	Battle(Game* game, std::vector<int> enemyPartyIds);

	void start();
};

