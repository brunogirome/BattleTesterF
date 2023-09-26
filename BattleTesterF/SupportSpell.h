#pragma once

#include "SpellInterface.h"

#include "SupportBuffsEnum.h"

#include <string>

class SupportSpell : public SpellInterface
{
public:
	int Rounds;

	SupportBuffsEnum SupportBuff;

	SupportSpell(int id, std::string name, std::string description, int rounds, SupportBuffsEnum supportBuff);
};
