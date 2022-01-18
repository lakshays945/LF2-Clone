#pragma once
#include "GameObject/GameObject.h"
#include "Common/AnimationSheet.h"
#include "Common/HitBox.h"

class Tornado : public GameObject {
public:
	Tornado();
	AnimationSheet TornadoSheet;
	GameObject* Parent = nullptr;
	void Instantiate(RealVector2D position);
	void GoBack();
	void AssignParent(GameObject* parent);
	void OnCollision(int otherID, int selfID);
	void Animate(sf::RenderWindow& window, const double dt);
};