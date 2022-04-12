#pragma once
#include "Common/ProjectileBall.h"

class DavisBlueBall : public ProjectileBall {
public:
	DavisBlueBall();
	void Animate(sf::RenderWindow& window, const double dt);
	void OnCollisionExit(int otherID, int selfID);
	void OnCollision(int otherID, int selfID);
};