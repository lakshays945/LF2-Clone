#pragma once
#include "GameObject/GameObject.h"
#include"Common/AnimationSheet.h"
#include "Common/HitBox.h"

class BlueBall : public GameObject {
private:
	GameObject* Parent = nullptr;
public:
	BlueBall();
	AnimationSheet InAirSheet;
	AnimationSheet EndSheet;
	AnimationSheet* CurrentSheet;
	HitBox AttackHitBox;
	void Animate(sf::RenderWindow& window, const double dt);
	void Instantiate(RealVector2D velocity = { 0,0 });
	void GoBack();
	void AssignParent(GameObject* parent);
	void OnCollision(int otherID, int selfID);
};