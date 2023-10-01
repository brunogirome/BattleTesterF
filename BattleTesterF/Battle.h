#pragma once

#include "Game.h"

#include "SupportSpell.h"

#include "FancyDialog.h"

enum battleStateEnum { STARTING, SELECT_ACTION, ENEMY_SELECTION, ACTOR_SELECTOR, HERO_ATTACKING, SPELL_SELECTION, SPELL_CASTING, ENEMY_TURN, DEFFENDING, ESCAPING, VICTORY, DEFEAT };

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
		TypeOfActorEnum TypeOfActor;

		actorAttackOrder(int position, int speed, TypeOfActorEnum typeOfActor, bool isDead);
	};

	class activeSupportBuff {
	public:
		SupportBuffsEnum SupportBuff;
		int ReamaningRounds;

		activeSupportBuff(SupportBuffsEnum supportBuff, int reamaningRounds);

		bool expired();
	};

	std::vector<activeSupportBuff> activeSupportBuffs;

	std::size_t currentAttackerPointer;

	std::size_t roundSize;

	int currentRound;

	std::vector<actorAttackOrder> attackOrder;

	actorAttackOrder* currentAttacker;

	void endOfTurn();

	// Battle State management/screens
	Enemy* currentEnemy;

	Hero* currentHero;

	CombatActorInterface* selectedBuffedActor;

	SpellInterface* selectedSpell;
	
	battleStateEnum battleState;

	bool castedSpell = false;

	void setNextState();

	void startingScreen();

	void selectActionScreen();

	void selectEnemyScreen();

	void selectActorScreen();

	void heroAttackingScreen();

	void selectSpellScreen();

	void castSpellScreen();

	void deffendingScreen();

	void escapingScreen();

	void enemyTurnScreen();

	void victoryScreen();

	void defeatScreen();

	// Utils
	void calculatePhysicalDamage(CombatActorInterface* attackerActor, CombatActorInterface* deffenderActor);


	// Aux render functions
	void printBattle();

	std::string getLine(int size, std::string character = "-");

	void drawLine(int size, bool border = false);
public:
	Battle(Game* game, std::vector<int> enemyPartyIds);

	void start();
};

