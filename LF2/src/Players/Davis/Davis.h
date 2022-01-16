#pragma once
#include "Common/Character.h"
#include "DavisBlueBall.h"

class Davis : public Character {
public:
	Davis();
	std::vector<DavisBlueBall> BallArray;
	void SpecialAttack1Calculations(const double dt, const double t);
	void SpecialAttack2Calculations(const double dt, const double t);
	void SpecialAttack3Calculations(const double dt, const double t);
};