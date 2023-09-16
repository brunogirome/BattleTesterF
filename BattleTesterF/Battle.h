#pragma once

#include "Game.h"
//#include "Hero.h";

enum class typeOfActorEnum { hero, enemy };

class Battle
{
private:
	Party* party;

	vector<Enemy> enemyParty;

	string getLine(int size, string character = "-");

	void drawLine(int size, bool border = false);

	class actorAttackOrder {
	public:
		int Position;
		int Speed;
		typeOfActorEnum TypeOfActor;

		actorAttackOrder(int position, int speed, typeOfActorEnum typeOfActor);
	};

	vector<actorAttackOrder> sortAttackOrder();

public:
	Battle(Game* game, vector<int> enemyPartyIds);

	void battleStart();

	void battleInterface();
};

