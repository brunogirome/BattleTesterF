#include "SupportSpell.h"

SupportSpell::SupportSpell(int id, std::string name, std::string description, int rounds, SupportBuffsEnum supportBuff)
	: SpellInterface(id, name, description, SUPPORT)
{
	this->Rounds = rounds;
	this->SupportBuff = supportBuff;
}
