#pragma once
#include "Common/ProjectileBall.h"

class DeepSlash : public ProjectileBall {
public:
	DeepSlash();
	double TotalTime = 0;
	void Animate(sf::RenderWindow& window, const double dt);
	void OnCollision(int otherID, int selfID);
	void OnCollisionExit(int otherID, int selfID);
};