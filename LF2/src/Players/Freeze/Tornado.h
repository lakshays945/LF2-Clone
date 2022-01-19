#pragma once
#include "Common/Character.h"

class Tornado : public GameObject {
public:
	Tornado();
	AnimationSheet TornadoSheet;
	GameObject* Parent = nullptr;
	double TotalTime = 0;
	HitBox AttackHitBox;
	HitBox ForceFieldBox;
	std::vector <Character*> CollidedPlayers;
	std::vector <bool> PlayersIn;
	void Instantiate(RealVector2D position);
	void GoBack();
	void AssignParent(GameObject* parent);
	void LiftPlayers(const double dt);
	void OnCollision(int otherID, int selfID);
	void Animate(sf::RenderWindow& window, const double dt);
};