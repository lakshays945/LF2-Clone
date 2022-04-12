#pragma once
#include "GameObject/GameObject.h"
#include "HitBox.h"
#include "AnimationSheet.h"
class ProjectileBall : public GameObject {
public:
	ProjectileBall();
	ProjectileBall(const ProjectileBall& other);
	GameObject* Parent = nullptr;
	HitBox AttackHitBox;
	HitBox ReboundHitBox;
	AnimationSheet InitialSheet;
	AnimationSheet InAirSheet;
	AnimationSheet FastSheet;
	AnimationSheet EndSheet;
	AnimationSheet* CurrentSheet;
	int MaxStrength = 150;
	int CurrentStrength = MaxStrength;
	bool Rebounded = false;
	void Instantiate(RealVector2D position, RealVector2D velocity = { 0,0 });
	void GoBack();
	void Rebound();
	void AssignParent(GameObject* parent);
	void SetScale(RealVector2D scale);
	virtual void OnCollision(int otherID, int selfID) = 0;
	virtual void OnCollisionExit(int otherID, int selfID) = 0;
	virtual void Animate(sf::RenderWindow& window, const double dt) = 0;
};