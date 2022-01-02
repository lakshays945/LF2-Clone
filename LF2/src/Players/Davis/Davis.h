#pragma once
#include "Common/Character.h"

class Davis : public Character {
public:
	Davis();
	void SpecialAttack1Calculations(const double dt, const double t);
	void SpecialAttack2Calculations(const double dt, const double t);
};