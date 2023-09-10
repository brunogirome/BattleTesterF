#include "CombatActorInterface.h"


void CombatActorInterface::initializeTotals() {
	// Setting basic status
	HpTotal = totalStatusFormula(HpBase, HP_MULTIPLIER, Strength, TYPE_STRENGTH);
	ManaTotal = totalStatusFormula(ManaBase, MANA_MULTIPLIER, Intelligence, TYPE_INTELLIGENCE);
	SpeedTotal = totalStatusFormula(SpeedBase, MANA_MULTIPLIER, Agility, TYPE_AGILITY);
	EvasionTotal = totalStatusFormula(EvasionBase, EVASION_MULTIPLIER, Agility, TYPE_AGILITY);
	StaminaTotal = totalStatusFormula(StaminaBase, STAMINA_MULTIPLIER, Agility, TYPE_AGILITY);

	// Setting damage status
	MeelePowerTotal = totalStatusFormula(MeelePowerBase, MEELE_POWER_MULTIPLIER, Strength, TYPE_STRENGTH);
	MagicPowerTotal = totalStatusFormula(MagicPowerBase, MAGIC_POWER_MULTIPLIER, Intelligence, TYPE_INTELLIGENCE);

	// Setting defense satus
	MeeleDefenseTotal = totalStatusFormula(MeeleDefenseBase, MEELE_DEFENSE_MULTIPLIER, Strength, TYPE_STRENGTH, "Calculate meele defense of ");
	MagicDefenseTotal = totalStatusFormula(MagicDefenseBase, MAGIC_DEFENSE_MULTIPLIER, Intelligence, TYPE_INTELLIGENCE, "Calculate magic defense of ");
}

int CombatActorInterface::totalStatusFormula(int baseStatus, float multiplier, int combatStatusValue, CombatTypesEnum combatStatusBonus, string debugMessage) {
	const int bonus = CombatType == combatStatusBonus ? 2 : 1;

	if (debugMessage != "")
		cout << debugMessage << Name << ": " << baseStatus << "+" << "((" << multiplier << "*" << combatStatusValue << ") * " << bonus << "));" << endl;

	return (int)round(baseStatus + ((multiplier * combatStatusValue) * bonus));
}
	