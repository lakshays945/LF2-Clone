#pragma once
#include "Common/Character.h"
#include "JohnBlueBall.h"
#include "JohnShield.h"
#include "DestructoDisk.h"
#include "Sparkle.h"

class John : public Character {
public:
	John();
	std::vector<JohnBlueBall> BallArray;
	std::vector<DestructoDisk> DiskArray;
	std::vector<JohnShield> ShieldArray;
	std::vector<Sparkle> SparkleArray;
	void SpecialAttack1Calculations(const double dt, const double t);
	void SpecialAttack2Calculations(const double dt, const double t);
	void SpecialAttack3Calculations(const double dt, const double t);
	void SpecialAttack4Calculations(const double dt, const double t);
};