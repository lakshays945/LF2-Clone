#pragma once
#include "GameObject/GameObject.h"
#include "Common/AnimationSheet.h"
#include "Common/HitBox.h"

enum WeaponType {
	WPN_TYPE_LIGHT = 0, WPN_TYPE_MEDIUM = 1, WPN_TYPE_HEAVY = 2
};

class Weapon : public GameObject {
protected:
public:
	static int nextID;
	Weapon();
	int WeaponID;
	AnimationSheet OnFloorSheet;
	AnimationSheet IdleSheet[4];
	AnimationSheet WalkingSheet[4];
	AnimationSheet RunningSheet[4];
	AnimationSheet JumpingSheet;
	AnimationSheet JumpAttackSheet;
	AnimationSheet HittingSheet[2];
	AnimationSheet DashSheet;
	AnimationSheet GettingHitSheet[2];
	AnimationSheet InAirSheet;
	AnimationSheet SpecialAttackSheet;
	AnimationSheet WobbleSheet;
	AnimationSheet* CurrentSheet;
	GameObject* CurrentParent = nullptr;
	WeaponType Type = WPN_TYPE_LIGHT;
	WeaponStates CurrentState = WPN_ON_FLOOR;
	HitBox AttackHitBox;
	HitBox PickUpHitBox;
	RealVector2D TargetPos;
	bool Hide = false;
	double InAirTime = 0.5;
	double GravityFactor = 0.75;
	void ChangeState(WeaponStates state, int data = 0);
	void AssignParent(GameObject* parent);
	void Update(const double dt);
	void Animate(sf::RenderWindow& window, const double dt);
	void SetPosition(RealVector2D position, double z_Position);
	void OnCollision(int otherID, int selfID);
	void OnCollisionExit(int otherID, int selfID);
	void InAirCalculations(const double dt);
	void Throw(RealVector2D velocity, bool attack = false);
	void Stop();
	void Translate(const double dt);
	void RegisterWeaponID();
};

extern std::vector<Weapon*> WeaponIDArray;