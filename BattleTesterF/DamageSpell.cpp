#include "DamageSpell.h"

DamageSpell::DamageSpell(int id, std::string name, std::string description, ElementsEnum element, int damage)
	: SpellInterface(id, name, description, DAMAGE)
{
	this->Element = element;
	this->Damage = damage;
}
