#include "CombatActorInterface.h"

CombatActorInterface::CombatActorInterface(int id, std::string name, TypeOfActorEnum typeOfActor, CombatTypesEnum combatType, ElementsEnum element, int strength, int agility, int intelligence, int hpBase, int manaBase, int speedBase, int evasionBase, int staminaBase, int meelePowerBase, int magicPowerBase, int meeleDefenseBase, int magicDefenseBase, std::vector<int> spells)
{
	this->Id = id;
	this->Name = name;
	this->TypeOfActor = typeOfActor;
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

	this->calculateTotals();

	this->HpCurrent = this->HpTotal;
	this->ManaCurrent = this->ManaTotal;

	this->Spells = spells;
}

bool CombatActorInterface::isDead()
{
	return this->HpCurrent <= 0;
}

void CombatActorInterface::calculateTotals()
{
	auto findBuff = [](BuffTypesEnum buff, std::vector<ActiveBuff> buffs)
	{
		for (ActiveBuff& spell : buffs) {
			if (spell.Buff->BuffType == buff) {
				return spell.Buff->Multiplier;
			}
		}

		return 0.f;
	};

	// Setting basic status
	this->HpTotal = totalStatusFormula(this->HpBase, this->HP_MULTIPLIER, this->Strength, TYPE_STRENGTH, findBuff(HP_BUFF, this->ActiveBuffs));

	this->ManaTotal = totalStatusFormula(this->ManaBase, this->MANA_MULTIPLIER, this->Intelligence, TYPE_INTELLIGENCE, findBuff(MANA_BUFF, this->ActiveBuffs));

	this->SpeedTotal = totalStatusFormula(this->SpeedBase, this->MANA_MULTIPLIER, this->Agility, TYPE_AGILITY, findBuff(SPEED_BUFF, this->ActiveBuffs));

	this->EvasionTotal = totalStatusFormula(this->EvasionBase, this->EVASION_MULTIPLIER, this->Agility, TYPE_AGILITY, findBuff(EVASION_BUFF, this->ActiveBuffs));

	this->StaminaTotal = totalStatusFormula(this->StaminaBase, this->STAMINA_MULTIPLIER, this->Agility, TYPE_AGILITY, findBuff(STAMINA_BUFF, this->ActiveBuffs));

	// Setting damage status
	this->MeelePowerTotal = totalStatusFormula(this->MeelePowerBase, this->MEELE_POWER_MULTIPLIER, this->Strength, TYPE_STRENGTH, findBuff(PHYSICAL_DAMAGE_BUFF, this->ActiveBuffs));

	this->MagicPowerTotal = totalStatusFormula(this->MagicPowerBase, this->MAGIC_POWER_MULTIPLIER, this->Intelligence, TYPE_INTELLIGENCE, findBuff(MAGIC_DAMAGE_BUFF, this->ActiveBuffs));

	// Setting defense satus
	this->MeeleDefenseTotal = totalStatusFormula(this->MeeleDefenseBase, this->MEELE_DEFENSE_MULTIPLIER, this->Strength, TYPE_STRENGTH, findBuff(PHYSICAL_DEFENSE_BUFF, this->ActiveBuffs));

	this->MagicDefenseTotal = totalStatusFormula(this->MagicDefenseBase, this->MAGIC_DEFENSE_MULTIPLIER, this->Intelligence, TYPE_INTELLIGENCE, findBuff(MAGIC_DEFENSE_BUFF, this->ActiveBuffs));
}

int CombatActorInterface::totalStatusFormula(int baseStatus, float multiplier, int combatStatusValue, CombatTypesEnum combatStatusBonus, float buff) {
	const int typeBonus = this->CombatType == combatStatusBonus ? 2 : 1;

	const float buffValue = 1 + buff;

	const float combatTypeBonus = multiplier * combatStatusValue * typeBonus;

	return (int)round((baseStatus + combatTypeBonus) * buffValue);
}

CombatActorInterface::ActiveBuff::ActiveBuff(BuffSpell* buff, int remaningRounds)
{
	this->Buff = buff;
	this->RemaningRounds = remaningRounds;
}
