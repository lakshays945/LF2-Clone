#pragma once
#include "Common/ProjectileBall.h"
#include "Common/Character.h"

class DestructoDisk : public ProjectileBall {
public:
	DestructoDisk();
	double TotalTime = 0;
	bool Collided = false;
	Character* Target = nullptr;
	void Animate(sf::RenderWindow& window, const double dt);
	bool SetTarget();
	void OnCollision(int otherID, int selfID);
	void CalculateVelocity(const double dt);
};