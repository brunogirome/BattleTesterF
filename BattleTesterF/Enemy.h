#pragma once

#include "CombatActorInterface.h"

class Enemy : public CombatActorInterface {
public:
	Enemy(int id, std::string name, CombatTypesEnum combatType, ElementsEnum element,
		int strength, int agility, int intelligence,
		int hpBase, int manaBase, int speedBase, int evasionBase, int staminaBase,
		int meelePowerBase, int magicPowerBase,
		int meeleDefenseBase, int magicDefenseBase, std::vector<int> spells);
};