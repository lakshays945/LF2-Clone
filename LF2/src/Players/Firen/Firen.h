#pragma once
#include "Common/Character.h"
#include "FirenFireBall.h"
#include "FirenGroundFire.h"
#include "FirenExplosion.h"
#include "FlameThrow.h"


class Firen : public Character {
public:
	Firen();
	std::vector<FirenFireBall> BallArray;
	std::vector<FirenGroundFire> GroundFireArray;
	std::vector<GroundFireHitBox> FireHitBoxArray;
	std::vector <FlameThrow> FlameThrowArray;
	FirenExplosionBox Firen_ExplosionBoxRD;
	FirenExplosionBox Firen_ExplosionBoxLD;
	FirenExplosionBox Firen_ExplosionBoxRU;
	FirenExplosionBox Firen_ExplosionBoxLU;
	FirenExplosionAnimation Firen_ExplosionAnimation;
	int FireSpawned = 0;
	int FireRunSpeed = 200;
	double FireRunSpawnRate = 0.15;
	void SpecialAttack1Calculations(const double dt, const double t);
	void SpecialAttack2Calculations(const double dt, const double t);
	void SpecialAttack3Calculations(const double dt, const double t);
	void SpecialAttack4Calculations(const double dt, const double t);
};