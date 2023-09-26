#pragma once

#include "SpellInterface.h"

#include "ElementsEnum.h"

class DamageSpell: public SpellInterface
{
public:
	ElementsEnum Element;

	int Damage;

	DamageSpell(int id, std::string name, std::string description, ElementsEnum element, int damage);
};

