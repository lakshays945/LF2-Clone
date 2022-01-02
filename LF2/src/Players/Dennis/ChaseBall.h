#pragma once
#include "GameObject/GameObject.h"
#include "Common/AnimationSheet.h"
#include "Common/HitBox.h"
#include "Common/Character.h"

class ChaseBall : public GameObject {
private:
	GameObject* Parent = nullptr;
public:
	ChaseBall();
	double TotalTime = 0;
	double MeanY;
	double InitialY;
	bool BeforeMean = true;
	Character* Target = nullptr;
	AnimationSheet InitialSheet;
	AnimationSheet ChaseModeSheet;
	AnimationSheet FastModeSheet;
	AnimationSheet EndSheet;
	AnimationSheet* CurrentSheet;
	HitBox AttackHitBox;
	void Animate(sf::RenderWindow& window, const double dt);
	void Instantiate(RealVector2D velocity = { 0,0 });
	void GoBack();
	void AssignParent(GameObject* parent);
	void OnCollision(int otherID, int selfID);
	void CalculateVelocity(const double dt);
};