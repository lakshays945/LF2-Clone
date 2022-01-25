#pragma once
#include "GameObject/GameObject.h"
#include "Common/AnimationSheet.h"
#include "Common/HitBox.h"
#include "Common/ProjectileBall.h"

class JohnShield : public GameObject {
public:
	JohnShield();
	AnimationSheet InitialSheet;
	AnimationSheet SteadySheet;
	AnimationSheet EndSheet;
	AnimationSheet* CurrentSheet;
	HitBox AttackHitBox;
	GameObject* Parent;
	double TotalTime = 0;
	void AssignParent(GameObject* parent);
	void Instantiate(RealVector2D position);
	void GoBack();
	void Animate(sf::RenderWindow& window, const double dt);
	void OnCollision(int otherID, int selfID);
	void OnCollisionExit(int otherID, int selfID);
};