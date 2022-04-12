#pragma once
#include "Common/ProjectileBall.h"

class FlameThrow : public ProjectileBall {
public:
	FlameThrow();
	double TotalTime = 0;
	void OnCollision(int otherID, int selfID);
	void OnCollisionExit(int otherID, int selfID);
	void Animate(sf::RenderWindow& window, const double dt);
};