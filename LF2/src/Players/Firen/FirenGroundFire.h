#pragma once
#include "Common/Character.h"
#include "Common/HitBox.h"
#include "Common/AnimationSheet.h"


class Firen;
class GroundFireHitBox : public GameObject {
public:
	double TotalTime = 0;
	double MaxTime = 3;
	int Extinguished = 0;
	int Spawned = 0;
	int ParentSpeed = 300;
	double SpawnRate = 0.1;
	bool Stopped = false;
	GroundFireHitBox();
	Firen* Parent = nullptr;
	HitBox AttackHitBox;
	void AssignParent(Firen* parent);
	void Instantiate(RealVector2D position);
	void Animate(sf::RenderWindow& window, const double dt);
	void OnCollision(int otherID, int selfID);
	void OnCollisionExit(int otherID, int selfID);
};

class FirenGroundFire : public GameObject {
public:
	FirenGroundFire();
	GameObject* Parent = nullptr;
	AnimationSheet InitialSheet;
	AnimationSheet BurnSheet;
	AnimationSheet EndSheet;
	AnimationSheet* CurrentSheet;
	double TotalTime = 0;
	double MaxTime = 3;
	void SetScale(RealVector2D scale);
	void Instantiate(RealVector2D position);
	void GoBack();
	void Rebound();
	void AssignParent(GameObject* parent);
	void Animate(sf::RenderWindow &window, const double dt);
	void OnCollision(int otherID, int selfID);
	void OnCollisionExit(int otherID, int selfID);
};