#pragma once
#include "Common/Character.h"
#include "BlueBall.h"
#include "ChaseBall.h"

class Dennis : public Character {
public:
	Dennis();
	std::vector<BlueBall> BallArray;
	std::vector<ChaseBall> ChaseBallArray;
	void SpecialAttack1Calculations(const double dt, const double t);
	void SpecialAttack2Calculations(const double dt, const double t);
};