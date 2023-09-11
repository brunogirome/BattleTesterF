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

	class tempSpeedActor {
	public:
		int Position;
		int Speed;
		typeOfActorEnum TypeOfActor;

		tempSpeedActor(int position, int speed, typeOfActorEnum typeOfActor);
	};

	vector<tempSpeedActor> sortAttackOrder();

public:
	Battle(Game* game, vector<int> enemyPartyIds);

	void battleStart();

	void battleInterface();
};

