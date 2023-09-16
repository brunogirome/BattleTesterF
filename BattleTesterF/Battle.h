#pragma once

#include "Game.h"
//#include "Hero.h";

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

	vector<Enemy> enemyParty;

	vector<actorAttackOrder> attackOrder;

	int currentRound;

	string getLine(int size, string character = "-");

	bool loop();

	void drawLine(int size, bool border = false);

	void sortAttackOrder();

	void selectAction(int attackerPosition);

	void printBattle();
public:
	Battle(Game* game, vector<int> enemyPartyIds);

	void start();
};

