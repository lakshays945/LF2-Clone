#pragma once
#include "Common/Character.h"
#include "FreezeBall.h"
#include "IceBerg.h"
#include "Tornado.h"
#include "Weapons/IceSword.h"
class Freeze : public Character {
public:
	Freeze();
	std::vector <FreezeBall> BallArray;
	std::vector <IceBerg> BergArray1;
	std::vector <IceBerg> BergArray2;
	std::vector <IceBerg> BergArray3;
	Tornado Freeze_Tornado;
	int IceBergIndex = 0;
	void SpecialAttack1Calculations(const double dt, const double t);
	void SpecialAttack2Calculations(const double dt, const double t);
	void SpecialAttack3Calculations(const double dt, const double t);
	void SpecialAttack4Calculations(const double dt, const double t);
};