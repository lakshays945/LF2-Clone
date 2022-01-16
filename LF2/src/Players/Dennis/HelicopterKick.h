#pragma once
#include "GameObject/GameObject.h"
#include "Common/HitBox.h"
class Dennis;
class HelicopterKick : public GameObject {
public:
	HitBox RegisterHitBox;
	HitBox ProjectileReboundHitBox;
	Dennis* Parent = nullptr;
	std::vector <int> HitCountArray;
	HelicopterKick();
	void Instantiate(RealVector2D position);
	void AssignParent(Dennis* parent);
	void Animate(sf::RenderWindow& window, const double dt);
	void OnCollision(int otherID, int selfID);
	void GoBack();
};