#pragma once

#include "CombatActorInterface.h";

class Hero: public CombatActorInterface {
public:
	Hero(int id, string name, CombatTypesEnum combatType, ElementsEnum element,
		int strength, int agility, int intelligence,
		int hpBase, int manaBase, int speedBase, int evasionBase, int staminaBase,
		int meelePowerBase, int magicPowerBase,
		int meeleDefenseBase, int magicDefenseBase);
};