#pragma once

#include "Game.h"

#include "SupportSpell.h"

#include "FancyDialog.h"

enum class typeOfActorEnum { hero, enemy };

class Battle
{
private:
	class actorAttackOrder {
	public:
		int Position;
		int Speed;
		bool IsDead;
		typeOfActorEnum TypeOfActor;

		actorAttackOrder(int position, int speed, typeOfActorEnum typeOfActor, bool isDead);
	};

	Party* party;

	std::vector<Enemy*> enemyParty;

	std::vector<actorAttackOrder> attackOrder;

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

