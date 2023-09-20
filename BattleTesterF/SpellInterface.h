#pragma once

#include <string>

#include "SpellTypesEnum.h"

class SpellInterface
{
public:
	int Id;
	std::string Name;
	std::string Description;

	SpellTypesEnum SpellType;

	SpellInterface(int id, std::string name, std::string description, SpellTypesEnum spellType);
};

