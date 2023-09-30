#pragma once
class Buff
{
public:
	int* Attribute;
	int Multiplier;
	int RemaningRounds;

	Buff(int* attribute, int multiplier, int remaningRounds);

	bool expired();
};

