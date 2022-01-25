#pragma once
#include "Common/ProjectileBall.h"

class JohnBlueBall : public ProjectileBall {
public:
	JohnBlueBall();
	void Animate(sf::RenderWindow& window, const double dt);
	void OnCollision(int otherID, int selfID);
	void OnCollisionExit(int otherID, int selfID);
};