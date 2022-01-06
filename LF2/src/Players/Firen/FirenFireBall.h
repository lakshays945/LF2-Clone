#pragma once
#include "Common/ProjectileBall.h"

class FirenFireBall : public ProjectileBall {
public:
	FirenFireBall();
	void Animate(sf::RenderWindow& window, const double dt);
	void OnCollision(int otherID, int selfID);
};