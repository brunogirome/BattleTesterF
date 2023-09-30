#include "BuffSpell.h"

BuffSpell::BuffSpell(int id, std::string name, std::string description, int rounds, BuffTypesEnum buffType, float multiplier)
	: SpellInterface(id, name, description, BUFF)
{
	this->Rounds = rounds;
	this->BuffType = buffType;
	this->Multiplier = multiplier;
}
