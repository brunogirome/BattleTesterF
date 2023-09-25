#include "SupportSpell.h"

SupportSpell::SupportSpell(int id, std::string name, std::string description, SpellTypesEnum spellType, int rounds, SupportBuffsEnum supportBuff)
	: SpellInterface(id, name, description, spellType)
{
	this->Rounds = rounds;
	this->SupportBuff = supportBuff;
}
