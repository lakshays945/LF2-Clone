#pragma once
#include "Common/Character.h"
#include "DeepSlash.h"

class Deep : public Character {
public:
	Deep();
	std::vector<DeepSlash> SlashArray;
	void SpecialAttack1Calculations(const double dt, const double t);
	void SpecialAttack2Calculations(const double dt, const double t);
	void SpecialAttack3Calculations(const double dt, const double t);
	void SpecialAttack4Calculations(const double dt, const double t);
};