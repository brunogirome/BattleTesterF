#pragma once

#include "SpellInterface.h"

#include "BuffTypesEnum.h"

class BuffSpell: public SpellInterface
{
public:
	int Rounds;

	float Multiplier;

	BuffTypesEnum BuffType;

	BuffSpell(int id, std::string name, std::string description, int rounds, BuffTypesEnum buffType, float multiplier);
};

