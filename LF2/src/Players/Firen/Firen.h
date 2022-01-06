#pragma once
#include "Common/Character.h"
#include "FirenFireBall.h"
#include "FirenGroundFire.h"

class Firen : public Character {
public:
	Firen();
	std::vector<FirenFireBall> BallArray;
	std::vector<FirenGroundFire> GroundFireArray;
	std::vector<GroundFireHitBox> FireHitBoxArray;
	int FireSpawned = 0;
	int FireRunSpeed = 200;
	double FireRunSpawnRate = 0.15;
	void SpecialAttack1Calculations(const double dt, const double t);
	void SpecialAttack2Calculations(const double dt, const double t);
};