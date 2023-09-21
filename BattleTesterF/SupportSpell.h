#pragma once

#include "SpellInterface.h"

#include "PartyBuffsEnum.h"

#include <string>

class SupportSpell: public SpellInterface
{
public:
	int Rounds;

	PartyBuffsEnum PartyBuff;

	SupportSpell(int id, std::string name, std::string description, SpellTypesEnum spellType, int rounds, PartyBuffsEnum partyBuff);
};

