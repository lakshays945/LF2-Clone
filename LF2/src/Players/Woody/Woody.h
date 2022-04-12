#pragma once
#include "Common/Character.h"
#include "WoodyBall.h"

class Woody : public Character {
public:
	Woody();
	std::vector<WoodyBall> BallArray;
	RealVector2D TargetPosition;
	void SpecialAttack1Calculations(const double dt, const double t);
	void SpecialAttack2Calculations(const double dt, const double t);
	void SpecialAttack3Calculations(const double dt, const double t);
	void SpecialAttack4Calculations(const double dt, const double t);
};
