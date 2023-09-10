#include "Hero.h"

Hero::Hero(int id, string name, CombatTypesEnum combatType, ElementsEnum element, int strength, int agility, int intelligence, int hpBase, int manaBase, int speedBase, int evasionBase, int staminaBase, int meelePowerBase, int magicPowerBase, int meeleDefenseBase, int magicDefenseBase)
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

	initializeTotals();
}
