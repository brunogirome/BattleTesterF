#pragma once

#include <string>
#include <vector>

#include "TypeOfActorEnum.h"
#include "CombatTypesEnum.h"
#include "ElementsEnum.h"

#include "BuffSpell.h"

class CombatActorInterface {
private:
	const float HP_MULTIPLIER = 2.5f;
	const float MANA_MULTIPLIER = 2.5f;
	const float SPEED_MULTIPLIER = 0.5f;
	const float EVASION_MULTIPLIER = 0.5f;
	const float STAMINA_MULTIPLIER = 0.25f;

	const float MEELE_POWER_MULTIPLIER = 1.25f;
	const float MAGIC_POWER_MULTIPLIER = 1.8f;

	const float MEELE_DEFENSE_MULTIPLIER = 0.5f;
	const float MAGIC_DEFENSE_MULTIPLIER = 0.5f;

	int totalStatusFormula(int baseStatus, float multiplier, int combatStatusValue, CombatTypesEnum combatStatusBonus, float buff = 0.f);

public:
	class ActiveBuff {
	public:
		BuffSpell* Buff;
		int RemaningRounds;

		ActiveBuff(BuffSpell* buff, int remaningRounds);

		bool expired();
	};

	CombatActorInterface(int id, std::string name, TypeOfActorEnum typeOfActor, CombatTypesEnum combatType, ElementsEnum element, int strength, int agility, int intelligence, int hpBase, int manaBase, int speedBase, int evasionBase, int staminaBase, int meelePowerBase, int magicPowerBase, int meeleDefenseBase, int magicDefenseBase, std::vector<int> spells);

	// General Status
	int Id;
	std::string Name;
	TypeOfActorEnum TypeOfActor;
	CombatTypesEnum CombatType;
	ElementsEnum Element;

	// Combat Type Status
	int Strength;
	int Agility;
	int Intelligence;

	// Base Combat Status
	int HpBase;
	int ManaBase;
	int SpeedBase;
	int EvasionBase;
	int StaminaBase;

	int MeelePowerBase;
	int MagicPowerBase;

	int MeeleDefenseBase;
	int MagicDefenseBase;

	// Effective Combat Status
	int HpTotal;
	int ManaTotal;
	int SpeedTotal;
	int EvasionTotal;
	int StaminaTotal;

	int MeelePowerTotal;
	int MagicPowerTotal;

	int MeeleDefenseTotal;
	int MagicDefenseTotal;

	int HpCurrent;
	int ManaCurrent;

	std::vector<int> Spells;

	std::vector<ActiveBuff> ActiveBuffs;

	bool isDead();

	int getOriginalHpTotal();

	int getOriginalManaTotal();

	void calculateTotals();
};