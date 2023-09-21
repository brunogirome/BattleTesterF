#include "Enemy.h"

Enemy::Enemy(int id, std::string name, CombatTypesEnum combatType, ElementsEnum element, int strength, int agility, int intelligence, int hpBase, int manaBase, int speedBase, int evasionBase, int staminaBase, int meelePowerBase, int magicPowerBase, int meeleDefenseBase, int magicDefenseBase, std::vector<SpellInterface> spells)
	: CombatActorInterface(id, name, combatType, element, strength, agility, intelligence, hpBase, manaBase, speedBase, evasionBase, staminaBase, meelePowerBase, magicPowerBase, meeleDefenseBase, magicDefenseBase, spells) 
{

}
