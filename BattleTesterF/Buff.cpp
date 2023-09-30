#include "Buff.h"

Buff::Buff(int* attribute, int multiplier, int remaningRounds)
{
	this->Attribute = attribute;
	this->Multiplier = multiplier;
	this->RemaningRounds = remaningRounds;
}

bool Buff::expired()
{
	return this->RemaningRounds < 1;
}
