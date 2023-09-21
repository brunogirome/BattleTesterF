#include "SupportSpell.h"

SupportSpell::SupportSpell(int id, std::string name, std::string description, SpellTypesEnum spellType, int rounds, PartyBuffsEnum partyBuff)
	:SpellInterface(id, name, description, spellType)
{
	this->Rounds = rounds;
	this->PartyBuff = partyBuff;
}
