#pragma once

#include <string>

#include "CombatTypesEnum.h"
#include "ElementsEnum.h"

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

	int totalStatusFormula(int baseStatus, float multiplier, int combatStatusValue, CombatTypesEnum combatStatusBonus);

public:
	void initializeTotals();

	// General Status
	int Id;
	std::string Name;
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

	// Other attributes
	// int SpellsId[];
};