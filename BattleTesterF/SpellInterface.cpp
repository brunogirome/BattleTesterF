#include "SpellInterface.h"

SpellInterface::SpellInterface(int id, std::string name, std::string description, SpellTypesEnum spellType)
{
	this->Id = id;
	this->Name = name;
	this->Description = description;
	this->SpellType = spellType;
}
