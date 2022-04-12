#pragma once
#include "Common/Character.h"
#include "Common/HitBox.h"
#include "Common/AnimationSheet.h"


class FirenExplosionBox : public GameObject {
public:
	FirenExplosionBox();
	double TotalTime = 0;
	RealVector2D Offset;
	HitBox ExplosionHitBox;
	GameObject* Parent = nullptr;
	void AssignOffset(RealVector2D offset);
	void Instantiate(RealVector2D position);
	void GoBack();
	void AssignParent(GameObject* parent);
	void Animate(sf::RenderWindow& window, const double dt);
	void OnCollision(int otherID, int selfID);
	void OnCollisionExit(int otherID, int selfID);
};

class FirenExplosionAnimation : public GameObject {
public:
	FirenExplosionAnimation();
	AnimationSheet ExplosionSheet;
	GameObject* Parent = nullptr;
	void Instantiate(RealVector2D position);
	void GoBack();
	void AssignParent(GameObject* parent);
	void Animate(sf::RenderWindow& window, const double dt);
	void OnCollision(int otherID, int selfID);
	void OnCollisionExit(int otherID, int selfID);
};

