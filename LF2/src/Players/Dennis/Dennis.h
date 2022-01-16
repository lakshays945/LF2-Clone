#pragma once
#include "Common/Character.h"
#include "DennisBlueBall.h"
#include "ChaseBall.h"
#include "HelicopterKick.h"

class Dennis : public Character {
public:
	Dennis();
	std::vector<DennisBlueBall> BallArray;
	std::vector<ChaseBall> ChaseBallArray;
	HelicopterKick Helicopter_Kick;
	void SpecialAttack1Calculations(const double dt, const double t);
	void SpecialAttack2Calculations(const double dt, const double t);
	void SpecialAttack3Calculations(const double dt, const double t);
};