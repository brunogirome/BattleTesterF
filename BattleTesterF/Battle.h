#pragma once

#include "Game.h"

#include "SupportSpell.h"

#include "FancyDialog.h"

enum typeOfActorEnum { HERO, ENEMY };

enum battleStateEnum { STARTING, SELECT_ACTION, ENEMY_SELECTION, HERO_ATTACKING, SPELL_SELECTION, SPELL_CASTING, ENEMY_TURN, DEFFENDING, ESCAPING, VICTORY, DEFEAT };

class Battle
{
private:
	std::vector<Hero*> party;

	Database* database;

	std::vector<Enemy> enemyParty;

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

	std::vector<activeSupportBuff> activeSupportBuffs;

	void manageSupportBuffs();

	std::size_t currentAttackerPointer;

	std::size_t roundSize;

	std::vector<actorAttackOrder> attackOrder;

	actorAttackOrder* currentAttacker;

	void setNextAttacker();

	// Battle State management/screens
	Enemy* currentEnemy;

	Hero* currentHero;

	SpellInterface* selectedSpell;
	
	battleStateEnum battleState;

	void setNextState();

	void startingScreen();

	void selectActionScreen();

	void selectEnemyScreen();

	void heroAttackingScreen();

	void selectSpellScreen();

	void castSpellScreen();

	void deffendingScreen();

	void escapingScreen();

	void enemyTurnScreen();

	// Utils
	void calculatePhysicalDamage(CombatActorInterface* attackerActor, CombatActorInterface* deffenderActor);

	int currentRound;

	// Aux render functions
	void printBattle();

	std::string getLine(int size, std::string character = "-");

	void drawLine(int size, bool border = false);
public:
	Battle(Game* game, std::vector<int> enemyPartyIds);

	void start();
};

