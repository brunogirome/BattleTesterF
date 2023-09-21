#include "CombatActorInterface.h"

CombatActorInterface::CombatActorInterface(int id, std::string name, CombatTypesEnum combatType, ElementsEnum element, int strength, int agility, int intelligence, int hpBase, int manaBase, int speedBase, int evasionBase, int staminaBase, int meelePowerBase, int magicPowerBase, int meeleDefenseBase, int magicDefenseBase, std::vector<SpellInterface> spells)
{
	this->Id = id;
	this->Name = name;
	this->CombatType = combatType;
	this->Element = element;
	this->Strength = strength;
	this->Agility = agility;
	this->Intelligence = intelligence;
	this->HpBase = hpBase;
	this->ManaBase = manaBase;
	this->SpeedBase = speedBase;
	this->EvasionBase = evasionBase;
	this->StaminaBase = staminaBase;
	this->MeelePowerBase = meelePowerBase;
	this->MagicPowerBase = magicPowerBase;
	this->MeeleDefenseBase = meeleDefenseBase;
	this->MagicDefenseBase = magicDefenseBase;

	// Setting basic status
	this->HpTotal = totalStatusFormula(HpBase, HP_MULTIPLIER, Strength, TYPE_STRENGTH);
	this->ManaTotal = totalStatusFormula(ManaBase, MANA_MULTIPLIER, Intelligence, TYPE_INTELLIGENCE);
	this->SpeedTotal = totalStatusFormula(SpeedBase, MANA_MULTIPLIER, Agility, TYPE_AGILITY);
	this->EvasionTotal = totalStatusFormula(EvasionBase, EVASION_MULTIPLIER, Agility, TYPE_AGILITY);
	this->StaminaTotal = totalStatusFormula(StaminaBase, STAMINA_MULTIPLIER, Agility, TYPE_AGILITY);

	// Setting damage status
	this->MeelePowerTotal = totalStatusFormula(MeelePowerBase, MEELE_POWER_MULTIPLIER, Strength, TYPE_STRENGTH);
	this->MagicPowerTotal = totalStatusFormula(MagicPowerBase, MAGIC_POWER_MULTIPLIER, Intelligence, TYPE_INTELLIGENCE);

	// Setting defense satus
	this->MeeleDefenseTotal = totalStatusFormula(MeeleDefenseBase, MEELE_DEFENSE_MULTIPLIER, Strength, TYPE_STRENGTH);
	this->MagicDefenseTotal = totalStatusFormula(MagicDefenseBase, MAGIC_DEFENSE_MULTIPLIER, Intelligence, TYPE_INTELLIGENCE);

	this->HpCurrent = this->HpTotal;
	this->ManaCurrent = this->ManaTotal;

	this->Spells = spells;
}

bool CombatActorInterface::isDead()
{
	return this->HpCurrent <= 0;
}

int CombatActorInterface::totalStatusFormula(int baseStatus, float multiplier, int combatStatusValue, CombatTypesEnum combatStatusBonus) {
	const int bonus = this->CombatType == combatStatusBonus ? 2 : 1;

	return (int)round(baseStatus + ((multiplier * combatStatusValue) * bonus));
}
	